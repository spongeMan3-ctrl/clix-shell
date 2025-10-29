<div align="center">

<pre>
   <strong>
     CCCC    L     I   X   X
    C    C   L     I    X X
    C        L     I     X
    C    C   L     I    X X
     CCCC   LLLL  I   X   X
   </strong>
</pre>

# CLIX (C Linux/UNIX Shell Interface)

**A simple, text-based shell written in C, inspired by the UNIX command line.**

<p>
  <img alt="Language" src="https://img.shields.io/badge/Language-C-blue.svg?style=for-the-badge">
  <img alt="Platform" src="https://img.shields.io/badge/Platform-Linux%20(POSIX)-green.svg?style=for-the-badge">
  <img alt="License" src="https://img.shields.io/badge/License-MIT-yellow.svg?style=for-the-badge">
</p>
</div>

---

## 🚀 About This Project

**CLIX** is a minimalist implementation of a system shell. This project was developed as a hands-on exercise in C system programming.

The primary goal was to understand how fundamental shell commands are built, how to interact with the file system at a low level, and how to handle user input/output using standard C libraries and system calls.

## ✨ Key Features

CLIX can interpret and execute a variety of built-in commands:

* `pwd` - Displays the current working directory.
* `ls` - Lists files and directories in the current location.
* `cd [path]` - Changes the current directory (supports `~`, `..`, and relative/absolute paths).
* `mkdir [name]` - Creates a new directory.
* `rmdir [name]` - Removes an empty directory.
* `touch [file]` - Creates a new, empty file.
* `rm [file]` - Deletes a file (not a directory).
* `cat [file]` - Displays the content of a text file to standard output.
* `echo [text]` - Prints the given text to standard output.
* `clear` - Clears the terminal screen (using ANSI escape codes).
* `help` - Displays the list of available commands.
* `clix` / `version` - Displays the project logo and version info.
* `exit 0` / `exit 1` - Terminates the CLIX shell.

## 🛠️ Tech Stack

This project is written entirely in **C** and relies heavily on the **POSIX API** for its functionality.

* **Language:** `C (C99)`
* **Core Libraries & APIs:**
    * `stdio.h`, `stdlib.h`, `string.h` - For basic I/O, memory allocation, and string operations.
    * `unistd.h` - Provides access to key POSIX functions (`getcwd`, `chdir`, `rmdir`).
    * `dirent.h` - Used for directory stream access (the `ls` command).
    * `sys/stat.h` - Required for creating directories (`mkdir`) with specific permissions.

## 🏁 Getting Started

This project has no external dependencies other than a standard C compiler (like `gcc`).

1.  **Clone the repository:**
    ```bash
    git clone [https://github.com/YOUR_USERNAME/YOUR_REPO_NAME.git](https://github.com/YOUR_USERNAME/YOUR_REPO_NAME.git)
    ```

2.  **Navigate to the directory:**
    ```bash
    cd YOUR_REPO_NAME
    ```

3.  **Compile the program:**
    (Assuming your source file is named `main.c`)
    ```bash
    gcc main.c -o clix
    ```

4.  **Run the shell:**
    ```bash
    ./clix
    ```

---

## 🖥️ An Important Note: Compatibility (Linux vs. Windows)

This project was **intentionally written for POSIX-compliant** operating systems (like Linux, macOS, BSD).

**The code in its current form will not compile or run on Windows.**

This is because it directly uses functions and header files that are specific to the POSIX standard and do not exist in the native Windows API:

* `#include <unistd.h>` (for `chdir`, `getcwd`, `rmdir`)
* `#include <dirent.h>` (for `opendir`, `readdir`, `closedir`)
* `#include <sys/stat.h>` (for the POSIX version of `mkdir`)
* The `getline()` function (which is a POSIX/GNU extension, not part of the ANSI C standard).
* Reliance on ANSI escape codes (e.g., `\033[...`) for colors and the `clear` command, which are not supported by default in older Windows `cmd` consoles.

To run this code on a Windows machine, one would need to use a compatibility layer like **WSL (Windows Subsystem for Linux)** or **MinGW**, or rewrite the POSIX-specific calls to use the native **Win32 API** (e.g., `<windows.h>`, `_mkdir`, `FindFirstFile`).

## 🔮 Future Improvements (TODO)

A list of features that could be added to enhance CLIX:

* [ ] **Proper Tokenization:** Implement `strtok_r` or a custom parser to handle arguments with spaces (e.g., `echo "Hello World"`).
* [ ] **External Program Execution:** Use `fork()` and `execvp()` to allow CLIX to run other system programs (like `nano`, `python`, etc.).
* [ ] **Pipes (`|`):** Add support for piping the output of one command to the input of another.
* [ ] **I/O Redirection:** Implement `>` (stdout) and `<` (stdin) redirection.
