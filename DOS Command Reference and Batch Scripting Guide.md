# 📄 DOS Command Reference & Batch Scripting Guide

## 1. **Basic DOS Commands**

### 1.1. `dir` – List files and directories

```bat
dir
```

* Shows files and directories in the current folder.
* Common switches:

  * `/p` – Pause after each screen.
  * `/w` – Wide listing format.
  * `/s` – Include subdirectories.

```bat
dir /p /w
```

**Example**: Show all `.txt` files in C:\Docs

```bat
dir C:\Docs\*.txt /s
```

### 1.2. `cd` – Change directory

```bat
cd \Projects
cd ..
```

* `..` moves up one directory.
* `\` goes to the root directory.

### 1.3. `md` or `mkdir` – Create directory

```bat
md C:\Projects\NewFolder
```

### 1.4. `rd` or `rmdir` – Remove directory

```bat
rd OldFolder
rd /s /q C:\Temp  :: Remove folder and all contents without asking
```

### 1.5. `copy` – Copy files

```bat
copy file.txt D:\Backup\
```

With wildcards:

```bat
copy *.txt D:\Backup\
```

### 1.6. `xcopy` – Extended copy

```bat
xcopy C:\Source D:\Target /E /H /C /I
```

* `/E` – Include subdirectories (even empty).
* `/H` – Include hidden files.
* `/C` – Continue even if errors occur.
* `/I` – Assume destination is a directory.

### 1.7. `move` – Move files or rename directories

```bat
move report.docx C:\Reports\
```

### 1.8. `del` or `erase` – Delete files

```bat
del file.txt
del /f /s *.tmp  :: Force delete, including subdirectories
```

### 1.9. `ren` – Rename file

```bat
ren oldname.txt newname.txt
```

---

## 2. **File and Text Operations**

### 2.1. `type` – Display file content

```bat
type readme.txt
```

### 2.2. `more` – Display file with pause

```bat
type largefile.txt | more
```

### 2.3. `find` – Search for text

```bat
find "keyword" file.txt
```

### 2.4. `findstr` – Advanced text search

```bat
findstr /i "error warning" *.log
```

---

## 3. **System Information Commands**

### 3.1. `echo` – Display messages

```bat
echo Hello World
echo.
```

* `echo.` outputs a blank line.
* Turn command echoing on/off:

```bat
echo off
echo on
```

### 3.2. `set` – Set environment variables

```bat
set NAME=Roberto
echo %NAME%
```

### 3.3. `set /p` – Prompt user input

```bat
set /p USERNAME=Enter your name: 
echo Hello %USERNAME%
```

### 3.4. `ver` – Show Windows version

```bat
ver
```

### 3.5. `time` / `date` – Show or set

```bat
time
date
```

---

## 4. **Wildcards**

* `*` – Matches any number of characters.
* `?` – Matches a single character.

**Examples**:

```bat
dir *.txt       :: All .txt files
dir data??.csv  :: Matches data01.csv, data02.csv...
```

---

## 5. **Batch Scripting Basics**

### 5.1. Create a simple `.bat` file

Example: `hello.bat`

```bat
@echo off
rem This is a comment
echo Hello, %1!
pause
```

Run:

```bat
hello Roberto
```

Output:

```
Hello, Roberto!
Press any key to continue...
```

**Note**: `%1` is the first parameter passed to the script.

---

### 5.2. Passing multiple parameters

```bat
@echo off
echo First: %1
echo Second: %2
```

Run:

```bat
params.bat apple banana
```

---

### 5.3. `shift` – Handle more than 9 parameters

```bat
@echo off
:loop
if "%1"=="" goto end
echo Parameter: %1
shift
goto loop
:end
```

---

### 5.4. Using variables inside batch

```bat
@echo off
set COUNT=5
echo We have %COUNT% files.
```

---

### 5.5. Conditional execution

```bat
if exist report.txt (
    echo Report found.
) else (
    echo Report missing.
)
```

---

### 5.6. Loops

```bat
for %%f in (*.txt) do (
    echo Processing %%f
)
```

**Note**: In the command line use `%f`, inside batch use `%%f`.

---

### 5.7. Using wildcards in loops

```bat
for %%f in (data??.csv) do (
    echo Found: %%f
)
```

---

### 5.8. Reading a file line by line

```bat
for /f "tokens=*" %%l in (list.txt) do (
    echo Line: %%l
)
```

---

### 5.9. Error handling

```bat
@echo off
copy file.txt D:\Backup\ || echo Copy failed!
```

---

## 6. **Practical Batch Example**

**Backup Script** – `backup.bat`

```bat
@echo off
rem === Backup Script ===
rem Usage: backup.bat source_folder destination_folder

if "%~1"=="" (
    echo Please specify a source folder.
    goto end
)
if "%~2"=="" (
    echo Please specify a destination folder.
    goto end
)

set SRC=%~1
set DEST=%~2

echo Backing up from %SRC% to %DEST%...
xcopy "%SRC%" "%DEST%" /E /H /C /I
echo Backup completed!
:end
pause
```

Run:

```bat
backup "C:\MyDocs" "D:\Backup\Docs"
```

---

## 7. **Tips**

* Always test scripts on a **safe folder** before running in production.
* Use `pause` to keep the window open for debugging.
* `%~dp0` inside a batch file returns the **directory of the script itself**.
* Redirect output:

```bat
dir > output.txt     :: Save output
dir >> output.txt    :: Append output
```
