# 📄 EBNF Specification for Turbo C

## 1. **Lexer Specification**

### 1.1. Tokens

```ebnf
letter         = "A"… "Z" | "a"… "z" | "_" ;
digit          = "0"… "9" ;
hexDigit       = digit | "A"… "F" | "a"… "f" ;

identifier     = letter , { letter | digit } ;

integerLiteral = decimalLiteral | octalLiteral | hexLiteral ;
decimalLiteral = digit , { digit } ;
octalLiteral   = "0" , { "0"… "7" } ;
hexLiteral     = ("0x" | "0X") , hexDigit , { hexDigit } ;

floatingLiteral = digit , { digit } , "." , { digit } , [ exponentPart ] , [ floatSuffix ] ;
exponentPart    = ("e" | "E") , [ "+" | "-" ] , digit , { digit } ;
floatSuffix     = "f" | "F" | "l" | "L" ;

charLiteral    = "'" , ( printableChar | escapeSequence ) , "'" ;
stringLiteral  = '"' , { printableChar | escapeSequence } , '"' ;

escapeSequence = "\\" , ( "'" | '"' | "?" | "\\" | "a" | "b" | "f" | "n" | "r" | "t" | "v"
                | octalDigit , [ octalDigit , [ octalDigit ] ]
                | "x" , hexDigit , { hexDigit } ) ;

printableChar  = ? any character except ' " \ and control chars ? ;
octalDigit     = "0"… "7" ;

comment        = "/*" , { anyCharExceptStarSlash } , "*/"
               | "//" , { anyCharExceptNewline } , newline ;

whitespace     = " " | "\t" | "\n" | "\r" ;
```

---

### 1.2. Keywords

```ebnf
keyword = "auto" | "break" | "case" | "char" | "const" | "continue" | "default" |
          "do" | "double" | "else" | "enum" | "extern" | "float" | "for" |
          "goto" | "if" | "int" | "long" | "register" | "return" | "short" |
          "signed" | "sizeof" | "static" | "struct" | "switch" | "typedef" |
          "union" | "unsigned" | "void" | "volatile" | "while";
```

---

### 1.3. Operators and Punctuation

```ebnf
operator = "+" | "-" | "*" | "/" | "%" |
           "++" | "--" |
           "==" | "!=" | ">" | "<" | ">=" | "<=" |
           "&&" | "||" | "!" |
           "&" | "|" | "^" | "~" | "<<" | ">>" |
           "=" | "+=" | "-=" | "*=" | "/=" | "%=" | "&=" | "|=" | "^=" | "<<=" | ">>=" |
           "->" | "." | "?" | ":" ;

punctuation = "(" | ")" | "{" | "}" | "[" | "]" | ";" | "," ;
```

---

## 2. **Parser Specification (EBNF)**

### 2.1. Program Structure

```ebnf
translationUnit = { externalDeclaration } ;

externalDeclaration = functionDefinition | declaration ;
```

---

### 2.2. Declarations

```ebnf
declaration = declarationSpecifiers , [ initDeclaratorList ] , ";" ;
declarationSpecifiers = { storageClassSpecifier | typeSpecifier | typeQualifier } ;

storageClassSpecifier = "auto" | "register" | "static" | "extern" | "typedef" ;
typeQualifier         = "const" | "volatile" ;

typeSpecifier =
    "void" | "char" | "short" | "int" | "long" | "float" | "double" |
    "signed" | "unsigned" | structOrUnionSpecifier | enumSpecifier | typedefName ;

structOrUnionSpecifier =
    ( "struct" | "union" ) , [ identifier ] , "{" , structDeclarationList , "}"
  | ( "struct" | "union" ) , identifier ;

structDeclarationList = { structDeclaration } ;
structDeclaration     = specifierQualifierList , structDeclaratorList , ";" ;
specifierQualifierList = { typeSpecifier | typeQualifier } ;
structDeclaratorList  = structDeclarator , { "," , structDeclarator } ;
structDeclarator      = [ pointer ] , declarator ;

enumSpecifier =
    "enum" , [ identifier ] , "{" , enumeratorList , "}"
  | "enum" , identifier ;
enumeratorList = enumerator , { "," , enumerator } ;
enumerator     = identifier , [ "=" , constantExpression ] ;

initDeclaratorList = initDeclarator , { "," , initDeclarator } ;
initDeclarator     = declarator , [ "=" , initializer ] ;
```

---

### 2.3. Declarators

```ebnf
declarator      = [ pointer ] , directDeclarator ;
directDeclarator =
    identifier
  | "(" , declarator , ")"
  | directDeclarator , "[" , [ constantExpression ] , "]"
  | directDeclarator , "(" , [ parameterTypeList | identifierList ] , ")" ;

pointer         = "*" , { typeQualifier } , [ pointer ] ;

parameterTypeList = parameterList , [ "," , "..." ] ;
parameterList      = parameterDeclaration , { "," , parameterDeclaration } ;
parameterDeclaration = declarationSpecifiers , [ declarator | abstractDeclarator ] ;

identifierList   = identifier , { "," , identifier } ;

typeName         = specifierQualifierList , [ abstractDeclarator ] ;

abstractDeclarator =
    pointer
  | [ pointer ] , directAbstractDeclarator ;

directAbstractDeclarator =
    "(" , abstractDeclarator , ")"
  | [ directAbstractDeclarator ] , "[" , [ constantExpression ] , "]"
  | [ directAbstractDeclarator ] , "(" , [ parameterTypeList ] , ")" ;
```

---

### 2.4. Statements

```ebnf
statement =
    labeledStatement
  | compoundStatement
  | expressionStatement
  | selectionStatement
  | iterationStatement
  | jumpStatement ;

labeledStatement =
    identifier , ":" , statement
  | "case" , constantExpression , ":" , statement
  | "default" , ":" , statement ;

compoundStatement = "{" , { declaration | statement } , "}" ;

expressionStatement = [ expression ] , ";" ;

selectionStatement =
    "if" , "(" , expression , ")" , statement , [ "else" , statement ]
  | "switch" , "(" , expression , ")" , statement ;

iterationStatement =
    "while" , "(" , expression , ")" , statement
  | "do" , statement , "while" , "(" , expression , ")" , ";"
  | "for" , "(" , [ expression ] , ";" , [ expression ] , ";" , [ expression ] , ")" , statement ;

jumpStatement =
    "goto" , identifier , ";"
  | "continue" , ";"
  | "break" , ";"
  | "return" , [ expression ] , ";" ;
```

---

### 2.5. Expressions

```ebnf
expression       = assignmentExpression , { "," , assignmentExpression } ;
assignmentExpression =
    conditionalExpression
  | unaryExpression , assignmentOperator , assignmentExpression ;

assignmentOperator =
    "=" | "*=" | "/=" | "%=" | "+=" | "-=" | "<<=" | ">>=" | "&=" | "^=" | "|=" ;

conditionalExpression =
    logicalOrExpression
  | logicalOrExpression , "?" , expression , ":" , conditionalExpression ;

logicalOrExpression  = logicalAndExpression , { "||" , logicalAndExpression } ;
logicalAndExpression = inclusiveOrExpression , { "&&" , inclusiveOrExpression } ;
inclusiveOrExpression = exclusiveOrExpression , { "|" , exclusiveOrExpression } ;
exclusiveOrExpression = andExpression , { "^" , andExpression } ;
andExpression        = equalityExpression , { "&" , equalityExpression } ;

equalityExpression   = relationalExpression , { ("==" | "!=") , relationalExpression } ;
relationalExpression = shiftExpression , { ("<" | ">" | "<=" | ">=") , shiftExpression } ;
shiftExpression      = additiveExpression , { ("<<" | ">>") , additiveExpression } ;

additiveExpression   = multiplicativeExpression , { ("+" | "-") , multiplicativeExpression } ;
multiplicativeExpression = castExpression , { ("*" | "/" | "%") , castExpression } ;

castExpression       = unaryExpression | "(" , typeName , ")" , castExpression ;

unaryExpression      =
    postfixExpression
  | "++" , unaryExpression
  | "--" , unaryExpression
  | unaryOperator , castExpression
  | "sizeof" , unaryExpression
  | "sizeof" , "(" , typeName , ")" ;

unaryOperator = "&" | "*" | "+" | "-" | "~" | "!" ;

postfixExpression =
    primaryExpression
  | postfixExpression , "[" , expression , "]"
  | postfixExpression , "(" , [ argumentExpressionList ] , ")"
  | postfixExpression , "." , identifier
  | postfixExpression , "->" , identifier
  | postfixExpression , "++"
  | postfixExpression , "--" ;

primaryExpression =
    identifier
  | constant
  | stringLiteral
  | "(" , expression , ")" ;

argumentExpressionList = assignmentExpression , { "," , assignmentExpression } ;

constant = integerLiteral | floatingLiteral | charLiteral ;
```

