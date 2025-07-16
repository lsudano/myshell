# MyShell 

A basic custom shell written in C.
Built as part of my "Build Your Own X" systems programming journey.

##  Features

Built-in `cd` and `exit` commands

Executes external programs via `execvp`

Handles user input, command parsing, and process control

Written in pure C on Linux (tested on Arch)

##  Concepts Covered

Forking and process creation

System calls (`execvp`, `chdir`, `wait`)

Tokenization with `strtok`

Input handling with `fgets`

##  How to Build

```bash
  gcc myshell.c -o myshell
./myshell
```
