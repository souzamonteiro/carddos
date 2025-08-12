# EBNF Grammar for DOS Batch Script

````ebnf
BatchScript     ::= { Statement }

Statement       ::= Command | Label | Comment | EmptyLine

Command         ::= SimpleCommand [ LineContinuation ]

SimpleCommand   ::= CommandName { WS Argument } NewLine

CommandName     ::= Identifier

Argument        ::= QuotedString | UnquotedString | VariableReference | Wildcard

Label           ::= ":" LabelName NewLine

LabelName       ::= Identifier

Comment         ::= "rem" WS CommentText NewLine

CommentText     ::= { AnyCharExceptNewLine }

VariableReference ::= "%" Identifier "%"

Wildcard        ::= "*" | "?"

QuotedString    ::= '"' { AnyCharExceptQuote } '"'

UnquotedString  ::= { AnyCharExceptWSNewline }

LineContinuation ::= "^" NewLine

Identifier      ::= Letter { Letter | Digit | "_" | "-" | "." }

Letter          ::= "A" | ... | "Z" | "a" | ... | "z"

Digit           ::= "0" | "1" | "2" | "3" | "4" | "5" | "6" | "7" | "8" | "9"

WS              ::= " " | "\t"

NewLine        ::= "\r\n" | "\n"

AnyCharExceptNewLine ::= any character except "\r" or "\n"

AnyCharExceptQuote   ::= any character except '"'

AnyCharExceptWSNewline ::= any character except whitespace or newline

---

### Control Structures and Special Commands

CommandName can be:

- `if`
- `goto`
- `call`
- `for`
- `set`
- `echo`
- `pause`
- `exit`
- `shift`
- any external command or internal DOS command

---

### Specific Command Syntaxes

#### IF Statement

```ebnf
IfCommand      ::= "if" WS ( Condition | ExistCondition ) WS Command

Condition      ::= VariableReference WS CompareOp WS Value

ExistCondition ::= "exist" WS FilePath

CompareOp      ::= "==" | "neq" | "lss" | "leq" | "gtr" | "geq"

Value          ::= QuotedString | UnquotedString
````

#### FOR Loop (Simplified DOS syntax)

```ebnf
ForCommand     ::= "for" WS ["%%" Identifier] WS "in" WS "(" FileSet ")" WS "do" WS Command

FileSet        ::= { UnquotedString { WS UnquotedString } }
```

#### GOTO Statement

```ebnf
GotoCommand    ::= "goto" WS LabelName
```

#### CALL Statement

```ebnf
CallCommand    ::= "call" WS ( LabelName | FileName ) [ WS ArgumentList ]
```

#### SET Statement

```ebnf
SetCommand     ::= "set" WS VariableAssignment

VariableAssignment ::= Identifier "=" Value
```

---

### Notes

* Variable references use `%VAR%` syntax only (no delayed expansion `!VAR!` in DOS).
* `for` loops use `%%` for variable tokens.
* Comments only start with `rem`.
* No advanced `for /f` or `setlocal`/`endlocal` commands in pure DOS batch.
* Line continuation is supported with `^` at the end of the line.
* Commands are case-insensitive but usually uppercase in examples.

---

