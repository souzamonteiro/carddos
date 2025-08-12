# 📄 Turbo C – Expanded Cheat Sheet

## 1. **`conio.h` – Console I/O Functions**

| Function              | Description                              | Example                      |
| --------------------- | ---------------------------------------- | ---------------------------- |
| `clrscr()`            | Clear the screen                         | `clrscr();`                  |
| `getch()`             | Wait for key press, no echo              | `ch = getch();`              |
| `getche()`            | Wait for key press, echo                 | `ch = getche();`             |
| `kbhit()`             | Check if a key is pressed (non-blocking) | `if (kbhit()) ch = getch();` |
| `textcolor(c)`        | Set text color                           | `textcolor(RED);`            |
| `textbackground(c)`   | Set background color                     | `textbackground(BLUE);`      |
| `gotoxy(x,y)`         | Move cursor to position                  | `gotoxy(10,5);`              |
| `cprintf()`           | Print at current cursor pos (formatted)  | `cprintf("Hello %d", n);`    |
| `window(x1,y1,x2,y2)` | Set printable window                     | `window(5,5,40,20);`         |
| `clreol()`            | Clear to end of line                     | `clreol();`                  |

**Color Constants:**

```
BLACK=0, BLUE=1, GREEN=2, CYAN=3, RED=4,
MAGENTA=5, BROWN=6, LIGHTGRAY=7, DARKGRAY=8,
LIGHTBLUE=9, LIGHTGREEN=10, LIGHTCYAN=11, LIGHTRED=12,
LIGHTMAGENTA=13, YELLOW=14, WHITE=15
```

---

## 2. **`graphics.h` – Graphics Functions**

**Initialization:**

```c
#include <graphics.h>
int gd = DETECT, gm;
initgraph(&gd, &gm, "C:\\Turboc3\\BGI");
```

**Basic Drawing Functions:**

| Function                       | Description          | Example                         |
| ------------------------------ | -------------------- | ------------------------------- |
| `line(x1,y1,x2,y2)`            | Draw line            | `line(10,10,100,100);`          |
| `rectangle(x1,y1,x2,y2)`       | Draw rectangle       | `rectangle(50,50,150,100);`     |
| `circle(x,y,r)`                | Draw circle          | `circle(200,200,50);`           |
| `ellipse(x,y,start,end,rx,ry)` | Draw ellipse         | `ellipse(200,200,0,360,50,30);` |
| `arc(x,y,start,end,r)`         | Draw arc             | `arc(200,200,0,180,50);`        |
| `putpixel(x,y,color)`          | Plot a pixel         | `putpixel(100,100,RED);`        |
| `getpixel(x,y)`                | Get pixel color      | `c = getpixel(100,100);`        |
| `setcolor(c)`                  | Set drawing color    | `setcolor(YELLOW);`             |
| `setbkcolor(c)`                | Set background color | `setbkcolor(BLUE);`             |
| `floodfill(x,y,border)`        | Fill area            | `floodfill(60,60,WHITE);`       |
| `bar(x1,y1,x2,y2)`             | Filled rectangle     | `bar(50,50,150,150);`           |
| `bar3d(...)`                   | 3D bar chart         | `bar3d(100,100,200,200,20,1);`  |
| `pieslice(x,y,start,end,r)`    | Pie slice            | `pieslice(200,200,0,90,50);`    |
| `drawpoly(n,points)`           | Polygon              | See example below               |

**Polygon Example:**

```c
int poly[] = {100,100, 150,50, 200,100, 150,150, 100,100};
drawpoly(5, poly);
```

---

## 3. **Turbo C IDE Keyboard Shortcuts**

| Shortcut     | Action                     |
| ------------ | -------------------------- |
| **F2**       | Save file                  |
| **F3**       | Open file                  |
| **F9**       | Compile & Link             |
| **Ctrl+F9**  | Run program                |
| **Alt+F5**   | View program output        |
| **F5**       | Zoom window                |
| **F1**       | Help                       |
| **F6**       | Switch between code/output |
| **F7**       | Step into (debug)          |
| **F8**       | Step over (debug)          |
| **Alt+X**    | Exit Turbo C               |
| **Ctrl+K+D** | Duplicate line             |
| **Ctrl+Y**   | Delete line                |
| **Ctrl+Q+I** | Indent block               |
| **Ctrl+Q+U** | Unindent block             |

---

## 4. **Practical Examples**

### 4.1. Console Colors & Movement

```c
#include <conio.h>

int main() {
    clrscr();
    textcolor(YELLOW);
    textbackground(BLUE);
    gotoxy(10,5);
    cprintf("Hello Turbo C!");
    getch();
    return 0;
}
```

---

### 4.2. Simple Graphics Demo

```c
#include <graphics.h>
#include <conio.h>

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "C:\\Turboc3\\BGI");

    setcolor(RED);
    circle(200,200,50);

    setfillstyle(SOLID_FILL, YELLOW);
    floodfill(200,200,RED);

    getch();
    closegraph();
    return 0;
}
```

---

### 4.3. Animated Bouncing Ball

```c
#include <graphics.h>
#include <conio.h>

int main() {
    int gd = DETECT, gm;
    int x = 100, y = 100, dx = 2, dy = 2;

    initgraph(&gd, &gm, "C:\\Turboc3\\BGI");

    while (!kbhit()) {
        cleardevice();
        setcolor(RED);
        circle(x, y, 20);
        delay(10);

        x += dx;
        y += dy;

        if (x <= 20 || x >= getmaxx()-20) dx = -dx;
        if (y <= 20 || y >= getmaxy()-20) dy = -dy;
    }

    closegraph();
    return 0;
}
```

