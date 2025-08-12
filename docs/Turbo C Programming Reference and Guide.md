# 📄 Turbo C Programming Reference & Guide

**Turbo C** is a C compiler and IDE by Borland (mostly used in DOS environments).
It includes a full-screen editor, compiler, linker, and debugger in one package.

---

## 1. **Starting Turbo C**

From DOS:

```dos
tc
```

Or with a file:

```dos
tc myprog.c
```

Inside Turbo C:

* **F9** → Compile and Link
* **Ctrl+F9** → Run
* **Alt+F5** → View output screen
* **F7/F8** → Step into/over for debugging

---

## 2. **Basic Program Structure**

```c
#include <stdio.h>   /* Standard I/O library */

int main() {
    printf("Hello, World!\n");
    return 0;
}
```

* `#include` imports header files.
* `main()` is the program entry point.
* `printf()` outputs text.
* `return 0;` ends the program successfully.

---

## 3. **Data Types**

| Type     | Description               | Example                |
| -------- | ------------------------- | ---------------------- |
| `int`    | Integer                   | `int a = 10;`          |
| `float`  | Floating-point (6 digits) | `float pi = 3.14;`     |
| `double` | Double precision          | `double x = 1.234567;` |
| `char`   | Single character          | `char c = 'A';`        |

Modifiers:

* `short`, `long`, `unsigned`, `signed`.

Example:

```c
unsigned int count = 100;
long bigNumber = 100000L;
```

---

## 4. **Input / Output**

```c
#include <stdio.h>

int main() {
    int age;
    char name[20];

    printf("Enter your name: ");
    scanf("%s", name);

    printf("Enter your age: ");
    scanf("%d", &age);

    printf("Hello %s, you are %d years old.\n", name, age);
    return 0;
}
```

**Note**: `scanf` requires `&` before variables (except strings).

---

## 5. **Operators**

* Arithmetic: `+ - * / %`
* Relational: `== != > < >= <=`
* Logical: `&& || !`
* Assignment: `= += -= *= /= %=`
* Increment/Decrement: `++ --`

---

## 6. **Control Structures**

### 6.1. If / Else

```c
if (score >= 50) {
    printf("Passed\n");
} else {
    printf("Failed\n");
}
```

### 6.2. Switch

```c
switch(choice) {
    case 1: printf("Option 1\n"); break;
    case 2: printf("Option 2\n"); break;
    default: printf("Invalid\n");
}
```

### 6.3. Loops

```c
for (int i = 1; i <= 5; i++) {
    printf("%d\n", i);
}

int x = 1;
while (x <= 5) {
    printf("%d\n", x++);
}

do {
    printf("%d\n", x--);
} while (x > 0);
```

---

## 7. **Functions**

```c
#include <stdio.h>

int square(int n) {
    return n * n;
}

int main() {
    printf("%d\n", square(5));
    return 0;
}
```

---

## 8. **Arrays**

```c
int nums[5] = {1, 2, 3, 4, 5};
for (int i = 0; i < 5; i++) {
    printf("%d ", nums[i]);
}
```

---

## 9. **Strings**

```c
#include <stdio.h>
#include <string.h>

int main() {
    char str[20] = "Turbo";
    strcat(str, " C");
    printf("%s\n", str);
    printf("Length: %d\n", strlen(str));
    return 0;
}
```

---

## 10. **Pointers**

```c
int a = 10;
int *p = &a;
printf("Value: %d\n", *p);
```

---

## 11. **File Handling**

```c
#include <stdio.h>

int main() {
    FILE *fp = fopen("test.txt", "w");
    fprintf(fp, "Hello File");
    fclose(fp);

    fp = fopen("test.txt", "r");
    char line[50];
    fgets(line, sizeof(line), fp);
    printf("%s\n", line);
    fclose(fp);
    return 0;
}
```

---

## 12. **Graphics in Turbo C**

```c
#include <graphics.h>

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "C:\\Turboc3\\BGI");

    circle(200, 200, 50);
    getch();
    closegraph();
    return 0;
}
```

**Note**: Requires `graphics.h` and BGI drivers in Turbo C.

---

## 13. **Example Programs**

### 13.1. Multiplication Table

```c
#include <stdio.h>

int main() {
    int n;
    printf("Enter number: ");
    scanf("%d", &n);

    for (int i = 1; i <= 10; i++) {
        printf("%d x %d = %d\n", n, i, n * i);
    }
    return 0;
}
```

### 13.2. Guess the Number

```c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int secret, guess;
    srand(time(0));
    secret = rand() % 100 + 1;

    do {
        printf("Guess: ");
        scanf("%d", &guess);
        if (guess < secret) printf("Too low!\n");
        else if (guess > secret) printf("Too high!\n");
    } while (guess != secret);

    printf("Correct!\n");
    return 0;
}
```

---

## 14. **Tips for Day-to-Day Turbo C Use**

* Always `#include` necessary headers (`stdio.h`, `string.h`, `conio.h`, etc.).
* `clrscr();` clears the console (requires `conio.h`).
* `getch();` waits for a key press (requires `conio.h`).
* Save source files with `.C` extension.
* Remember Turbo C is **not ANSI C compliant** in some areas — modern compilers may need small changes.
