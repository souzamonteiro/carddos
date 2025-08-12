# EBNF Specification for QBasic

> Notas gerais:
>
> * Usamos a notação EBNF clássica: `X = ... ;`, `[...]` opcional, `{...}` repetição (0+), `(...)` agrupamento, `|` alternativa.
> * QBasic permite **números de linha opcionais** no início de uma linha (`linenumber`), e também **múltiplas instruções na mesma linha** separadas por `:`.
> * Variáveis podem ter **sufixos de tipo**: `%` (INTEGER), `&` (LONG), `!` (SINGLE), `#` (DOUBLE), `$` (STRING). Esses sufixos fazem parte do identificador tokenizado (ou podem ser analisados como parte do identificador).
> * Strings usam aspas duplas `"..."`. Escape em QB é por `""` para representar uma `"` dentro da string.
> * Comentários: `REM` até fim da linha ou `'` (apóstrofo) até fim da linha.

---

## 1) Lexer — tokens (definições lexis)

```ebnf
digit           = "0" … "9" ;
nonzeroDigit    = "1" … "9" ;
letter          = "A" … "Z" | "a" … "z" ;
underscore      = "_" ;

-- Identificadores e sufixos de tipo
typeSuffix      = "%" | "&" | "!" | "#" | "$" ;
identifierCore  = ( letter | "_" ) , { letter | digit | "_" } ;
identifier      = identifierCore , [ typeSuffix ] ;

-- Números (inteiros e ponto-flutuante)
integerLiteral  = digit , { digit } ;
floatLiteral    = ( digit , { digit } , "." , { digit } , [ exponentPart ] )
                | ( "." , digit , { digit } , [ exponentPart ] )
                | ( digit , { digit } , exponentPart ) ;
exponentPart    = ( "E" | "e" ) , [ "+" | "-" ] , digit , { digit } ;

numericLiteral  = floatLiteral | integerLiteral ;

-- Strings
stringLiteral   = '"' , { stringChar } , '"' ;
stringChar      = ? qualquer caractere exceto " ou controle ? 
                | '""'   -- duas aspas seguidas representam aspas no conteúdo

-- Comentários
lineComment     = "'" , { anyCharExceptNewline } ;
remComment      = "REM" , { " " } , { anyCharExceptNewline } ;

-- Separadores e pontuação
newline         = "\r\n" | "\n" | "\r" ;
space           = " " | "\t" ;
semicolon       = ":" ;        -- statement separator on same line
comma           = "," ;
lparen          = "(" ;
rparen          = ")" ;
lbrack          = "[" ;
rbrack          = "]" ;
eql             = "=" ;
plus            = "+" ;
minus           = "-" ;
mul             = "*" ;
div             = "/" ;
caret           = "^" ;
percent         = "%" ;        -- also used as suffix, but tokenized accordingly
lt              = "<" ;
gt              = ">" ;

-- Two-char/compound operators (tokenize longest first)
le              = "<=" ;
ge              = ">=" ;
ne              = "<>" | "!=" ; -- QB uses <> for not equal; some dialects accept !=
stringConcat    = "+" ;         -- in many QB dialects string concatenation uses + (or ;)
assignment      = "=" ;

-- Keywords (case-insensitive; treated as distinct tokens)
keyword = "PRINT" | "INPUT" | "LET" | "IF" | "THEN" | "ELSE" | "ELSEIF"
        | "FOR" | "TO" | "STEP" | "NEXT" | "WHILE" | "WEND" | "DO" | "LOOP"
        | "SELECT" | "CASE" | "END" | "SUB" | "FUNCTION" | "RETURN" | "GOTO" | "GOSUB"
        | "DIM" | "REDIM" | "AS" | "INTEGER" | "LONG" | "SINGLE" | "DOUBLE" | "STRING"
        | "STATIC" | "PUBLIC" | "LOCAL" | "DEF" | "FN" | "OPEN" | "CLOSE" | "GET" | "PUT"
        | "PRINT" | "LOCATE" | "CLS" | "SCREEN" | "COLOR" | "BEEP" | "REM" | "STEP"
        | "TO" | "UNTIL" | "LOOP" | "WHILE" | "WEND" | "EXIT" | "STOP" | "FIELD" | "SEEK"
        | "OPTION" | "BASE" | "COMMON" | "SHARED" | "ON" | "ERROR" | "RESUME" ;

-- Whitespace: skipped (except newline which delimits statements/lines)
whitespace      = { space | tab } ;
```

**Observações do lexer**

* QBasic é **case-insensitive**; o lexer normaliza palavras reservadas e identifiers para uma forma (por ex. maiúsculas) para comparação com `keyword`.
* Números com sufixos de tipo raramente aparecem (ex.: `1!`), mas a gramática de tokens pode aceitar `numericLiteral` seguido por typeSuffix se necessário.
* Comentários e espaços são descartados pelo lexer (nova linha sinaliza fim de statement a menos que haja `;` ou `,` em `PRINT`).

---

## 2) Parser — gramática EBNF (sintaxe)

### 2.1. Programa / Unidade

```ebnf
program         = { programLine } ;

programLine     = [ lineNumber ] , [ statementList ] , newline ;
lineNumber      = integerLiteral ;        -- optional, e.g. "10", if present used by GOTO/GOSUB

statementList   = statement , { ":" , statement } ;  -- multiple statements per physical line
```

---

### 2.2. Statements (alto nível)

```ebnf
statement =
      letStatement
    | printStatement
    | inputStatement
    | ifStatement
    | forStatement
    | whileStatement
    | doLoopStatement
    | selectCaseStatement
    | gotoStatement
    | gosubStatement
    | returnStatement
    | subDeclaration
    | functionDeclaration
    | dimStatement
    | redimStatement
    | openStatement
    | closeStatement
    | fileIOStatement
    | remStatement
    | stopStatement
    | endStatement
    | otherStatement ;  -- placeholder para comandos como CLS, BEEP, LOCATE, COLOR
```

---

### 2.3. Atribuição / LET

```ebnf
letStatement    = [ "LET" ] , variable , "=" , expression ;

variable        = identifier | arrayReference ;
arrayReference  = identifier , "(" , [ expressionList ] , ")" ;

expressionList  = expression , { "," , expression } ;
```

---

### 2.4. PRINT e PRINT USING

```ebnf
printStatement  = "PRINT" , [ printItems ] ;
printItems      = printItem , { "," | ";" , printItem } ;
printItem       = expression | stringLiteral | "TAB" "(" , expression , ")" ;
```

---

### 2.5. INPUT

```ebnf
inputStatement  = "INPUT" , [ stringLiteral , ":" ] , inputVarList ;
inputVarList    = inputVar , { "," , inputVar } ;
inputVar        = variable | "LINE INPUT" , variable ;
```

---

### 2.6. IF ... THEN ... \[ELSE / ELSEIF]

```ebnf
ifStatement =
      "IF" , expression , "THEN" , ( statement | statementList )
    , [ "ELSE" , ( statement | statementList ) ] ;

-- note: QBasic allows single-line IF with THEN followed by statements on same line,
-- or a block style using "IF ... THEN" / "ELSE" / "END IF" in some dialects.
```

---

### 2.7. FOR ... NEXT

```ebnf
forStatement =
    "FOR" , identifier , "=" , expression , "TO" , expression
    , [ "STEP" , expression ]
    , statementBodyFor ;

statementBodyFor =
    ( statementList ) |  -- single-line FOR ... NEXT
    ( { statement } , "NEXT" , [ identifier ] ) ;
```

---

### 2.8. WHILE / WEND

```ebnf
whileStatement =
    "WHILE" , expression , { statement } , "WEND" ;
```

---

### 2.9. DO ... LOOP

```ebnf
doLoopStatement =
    "DO" , { statement } , ( "LOOP" [ "WHILE" expression | "UNTIL" expression ] |
                             "WHILE" expression , "LOOP" |
                             "UNTIL" expression , "LOOP" ) ;
```

---

### 2.10. SELECT CASE

```ebnf
selectCaseStatement =
    "SELECT" , "CASE" , expression ,
       { caseClause }
    , [ "CASE" , "ELSE" , { statement } ]
    , "END" , "SELECT" ;

caseClause =
    "CASE" , caseExpressionList , { statement } ;

caseExpressionList =
    caseExpression , { "," , caseExpression } ;

caseExpression =
    "IS" , relationalOp , expression
  | expressionRange
  | expression ;            -- single value

relationalOp = "<" | ">" | "<=" | ">=" | "=" | "<>" ;
expressionRange = expression , "TO" , expression ;
```

---

### 2.11. GOTO / GOSUB / RETURN / END

```ebnf
gotoStatement    = "GOTO" , lineNumber ;
gosubStatement   = "GOSUB" , lineNumber ;
returnStatement  = "RETURN" ;
endStatement     = "END" ;
stopStatement    = "STOP" ;
```

---

### 2.12. SUB / FUNCTION Declarations

```ebnf
subDeclaration =
    "SUB" , identifier , [ "(" , [ paramList ] , ")" ] , newline
    , { statement }
    , "END" , "SUB" ;

functionDeclaration =
    "FUNCTION" , identifier , "(" , [ paramList ] , ")" , [ "AS" , typeName ] , newline
    , { statement }
    , "END" , "FUNCTION" ;

paramList = param , { "," , param } ;
param     = identifier , [ "AS" , typeName ] ;
typeName  = "INTEGER" | "LONG" | "SINGLE" | "DOUBLE" | "STRING" | identifier ;
```

---

### 2.13. DIM / REDIM

```ebnf
dimStatement = "DIM" , dimList ;
dimList      = dimDecl , { "," , dimDecl } ;
dimDecl      = identifier , "(" , dimensionList , ")" , [ "AS" , typeName ] ;

dimensionList = dimension , { "," , dimension } ;
dimension     = expression | expression , ":" , expression ; -- lower:upper optional in some dialects

redimStatement = "REDIM" , [ "PRESERVE" , ] , dimList ;
```

---

### 2.14. File I/O (OPEN, CLOSE, GET, PUT, WRITE, LINE INPUT)

```ebnf
openStatement = "OPEN" , stringLiteral , "FOR" , fileMode , [ "AS" , fileNumber ] ;
fileMode      = "INPUT" | "OUTPUT" | "APPEND" | "RANDOM" | "BINARY" | "RANDOM" ;
closeStatement = "CLOSE" , [ fileNumber | "ALL" ] ;

fileIOStatement =
    "GET" , fileNumber , "," , [ recordNumber ] , "," , variable
  | "PUT" , fileNumber , "," , [ recordNumber ] , "," , variable
  | "WRITE" , fileNumber , "," , writeItems
  | "LINE INPUT" , fileNumber , "," , variable
  | "INPUT" , fileNumber , "," , inputVarList ;
```

---

### 2.15. Expressions & Precedence

(Operadores em ordem de precedência decrescente)

```ebnf
expression =
    relationalExpression , { logicalOp , relationalExpression } ;

logicalOp = "AND" | "OR" | "NOT" ;  -- QB has AND/OR; NOT is unary

relationalExpression =
    additiveExpression , [ relation , additiveExpression ] ;
relation = "=" | "<>" | "<" | ">" | "<=" | ">=" ;

additiveExpression =
    multiplicativeExpression , { ("+" | "-" ) , multiplicativeExpression } ;

multiplicativeExpression =
    powerExpression , { ("*" | "/" | "\" | "MOD") , powerExpression } ;
    -- note: "\" integer division, MOD modulus operator in QB

powerExpression =
    unaryExpression , { "^" , unaryExpression } ;

unaryExpression =
    [ "+" | "-" ] , primaryExpression
  | "NOT" , primaryExpression ;

primaryExpression =
    literal
  | variable
  | "(" , expression , ")"
  | functionCall ;

literal =
    numericLiteral | stringLiteral ;

functionCall =
    identifier , "(" , [ expressionList ] , ")" ;
```

---

### 2.16. Outros detalhes sintáticos / semânticos

* **PRINT**: `PRINT` aceita `;` e `,` como separadores com semânticas diferentes (`,` tabula, `;` suprime nova linha); gramática acima simplifica como `printItems`.
* **LET** é opcional; atribuições podem ser `LET X = 1` ou `X = 1`.
* **IF single-line**: `IF cond THEN stmt1 : stmt2 : ...` é comum; também existe forma de bloco com `IF ... THEN ... ELSE ... END IF` em algumas variantes (QuickBASIC). Gramática cobre a forma básica.
* **LABELS**: Em versões sem número de linha, etiquetas de rótulo podem existir (identifiers seguidos de `:`) — a gramática do `programLine` permite `lineNumber` opcional; para labels simbólicos incluir `labelDefinition = identifier , ":"` se desejar.
* **DEF FN**: sintaxe: `DEF FNname(arg) = expression` — esta forma define funções inline (usar `DEF` handling especial).

```ebnf
defFn = "DEF" , "FN" , identifier , "(" , paramListSimple , ")" , "=" , expression ;
paramListSimple = identifier , { "," , identifier } ;
```

* **Sequência de término de programa**: `END` termina execução; `STOP` pausa.

---

## 3) Exemplos (curtos) — para verificar a gramática

1. Programa simples com **linha numerada** e `GOTO`:

```basic
10 PRINT "HELLO"
20 INPUT "YOUR NAME: ", N$
30 IF N$ = "" THEN GOTO 10
40 PRINT "WELCOME "; N$
50 END
```

2. Sub e Function:

```basic
SUB Hello(name$)
    PRINT "Hello "; name$
END SUB

FUNCTION Square(x)
    Square = x * x
END FUNCTION

CALL Hello("Roberto")
PRINT Square(5)
```

3. FOR / NEXT com STEP:

```basic
FOR i = 1 TO 10 STEP 2
    PRINT i;
NEXT i
```

4. Reading file / OPEN / INPUT:

```basic
OPEN "DATA.TXT" FOR INPUT AS #1
WHILE NOT EOF(1)
    LINE INPUT #1, L$
    PRINT L$
WEND
CLOSE #1
```

---

## 4) Notas práticas para implementação do lexer & parser

* **Lexer**:

  * normalize keywords (case-insensitive).
  * reconhecer `REM` seguido por espaço ou fim (REM pode aparecer sem espaço? normalmente `REM` seguido de qualquer coisa até fim da linha).
  * tratar `"` `""` escape dentro de `stringLiteral`.
  * reconhecer sufixos de variável como parte do identificador para simplificar (ou separar token `identifier` + `typeSuffix`).
  * tokenizar operadores de maior comprimento primeiro (`<=`, `>=`, `<>`) para evitar confusão com `<` `>`.

* **Parser**:

  * A gramática QBasic é relativamente simples (linhas sequenciais, statements com final de linha ou `:`). Ainda assim:

    * trate `INPUT` e `PRINT` com regras especiais (vírgula e ponto-e-vírgula têm comportamento semântico).
    * `FOR/NEXT`: manter pilha de loops durante parsing para detectar `NEXT` com identificador opcional.
    * `GOSUB/GOTO` resolvidos em fase de link/execução (labels numéricos ou simbólicos).
    * verificação de tipos: QBasic é fraco em tipagem; muitas conversões implícitas (ex.: concatenação string+number). Tipo rígido só para operações específicas.

---
