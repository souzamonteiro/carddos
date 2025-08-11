# 📄 QBasic Programming Reference & Guide

**QBasic** is an easy-to-learn programming language included in older versions of MS-DOS and early Windows.
It’s still useful for learning programming logic, making quick utilities, or running retro code.

---

## 1. **Starting QBasic**

* If QBasic is installed:

```dos
qbasic
```

* To run a program:

```dos
qbasic /run myprog.bas
```

---

## 2. **Basic Syntax**

### 2.1. **Printing Text**

```basic
PRINT "Hello, World!"
```

* `PRINT` outputs text to the screen.
* Use `;` to avoid a newline:

```basic
PRINT "Hello"; "World"
```

---

### 2.2. **Variables**

* No need to declare, but you can use `DIM` for clarity.
* Types:

  * Integer: `A%`
  * String: `Name$`
  * Single-precision float: `X!`
  * Double-precision: `Y#`

```basic
DIM Age AS INTEGER
DIM Name AS STRING
Age = 25
Name = "Roberto"
PRINT "Name:"; Name; "Age:"; Age
```

---

### 2.3. **Comments**

```basic
' This is a comment
REM Another comment style
```

---

### 2.4. **Input from User**

```basic
INPUT "Enter your name: ", UserName$
PRINT "Hello, "; UserName$
```

---

### 2.5. **Mathematics**

```basic
A = 5
B = 3
PRINT A + B   ' Addition
PRINT A - B   ' Subtraction
PRINT A * B   ' Multiplication
PRINT A / B   ' Division
PRINT A ^ B   ' Power
```

---

### 2.6. **Control Structures**

#### IF...THEN...ELSE

```basic
IF Age >= 18 THEN
    PRINT "Adult"
ELSE
    PRINT "Minor"
END IF
```

#### SELECT CASE

```basic
SELECT CASE Choice
    CASE 1
        PRINT "Option 1"
    CASE 2
        PRINT "Option 2"
    CASE ELSE
        PRINT "Invalid option"
END SELECT
```

#### FOR...NEXT loop

```basic
FOR I = 1 TO 10
    PRINT "Number"; I
NEXT I
```

#### WHILE...WEND loop

```basic
X = 1
WHILE X <= 5
    PRINT X
    X = X + 1
WEND
```

#### DO...LOOP

```basic
DO
    INPUT "Enter a number (0 to quit): ", N
LOOP UNTIL N = 0
```

---

## 3. **Working with Strings**

```basic
Text$ = "QBasic"
PRINT LEN(Text$)       ' Length of string
PRINT LEFT$(Text$, 3)  ' First 3 characters
PRINT RIGHT$(Text$, 2) ' Last 2 characters
PRINT MID$(Text$, 2, 3)' Characters 2 to 4
PRINT UCASE$(Text$)    ' Uppercase
PRINT LCASE$(Text$)    ' Lowercase
```

---

## 4. **Working with Files**

### 4.1. Writing to a File

```basic
OPEN "data.txt" FOR OUTPUT AS #1
PRINT #1, "Hello File"
CLOSE #1
```

### 4.2. Reading from a File

```basic
OPEN "data.txt" FOR INPUT AS #1
WHILE NOT EOF(1)
    LINE INPUT #1, Line$
    PRINT Line$
WEND
CLOSE #1
```

---

## 5. **Using Subroutines and Functions**

### SUB

```basic
SUB Greet(Name$)
    PRINT "Hello,"; Name$
END SUB

CALL Greet("Roberto")
```

### FUNCTION

```basic
FUNCTION Square(X)
    Square = X * X
END FUNCTION

PRINT Square(5)
```

---

## 6. **Using Arrays**

```basic
DIM Numbers(5) AS INTEGER
FOR I = 1 TO 5
    Numbers(I) = I * 10
NEXT I

FOR I = 1 TO 5
    PRINT Numbers(I)
NEXT I
```

---

## 7. **Example Programs**

### 7.1. Calculator

```basic
CLS
PRINT "Simple Calculator"
INPUT "Enter first number: ", A
INPUT "Enter second number: ", B
PRINT "Sum:"; A + B
PRINT "Difference:"; A - B
PRINT "Product:"; A * B
PRINT "Quotient:"; A / B
```

---

### 7.2. Multiplication Table

```basic
CLS
INPUT "Enter a number: ", N
FOR I = 1 TO 10
    PRINT N; "x"; I; "="; N * I
NEXT I
```

---

### 7.3. Guess the Number

```basic
RANDOMIZE TIMER
Secret = INT(RND * 100) + 1
DO
    INPUT "Guess the number (1-100): ", Guess
    IF Guess < Secret THEN PRINT "Too low!"
    IF Guess > Secret THEN PRINT "Too high!"
LOOP UNTIL Guess = Secret
PRINT "Correct!"
```

---

## 8. **Tips for Day-to-Day QBasic Use**

* Use `CLS` to clear the screen before drawing or printing.
* `COLOR foreground, background` changes text colors.
* `LOCATE row, col` positions the cursor.
* `BEEP` makes a simple sound.
* Save your code with `.BAS` extension.
* Use **labels** and `GOTO` only when necessary (structured loops are better).
