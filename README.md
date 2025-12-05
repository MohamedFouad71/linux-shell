# 🐧 Mini Linux Shell  
A simple Linux-like shell written in C for learning OS concepts, system calls, and command execution.

## 🚀 Overview
This project is a simple terminal, similar to a Linux shell, built to help us learn the core fundamentals of how shells work.
It covers essential concepts such as:
- Parsing  
- Tokenization  
- Process creation (fork)  
- Command execution (execvp)  
- Built-in commands  
- I/O Redirection  
- Piping  
- History  
- Colored prompt  

## 📁 Project Structure
```
.
├── Makefile
├── README.md
├── include
│   ├── builtins.h
│   ├── executor.h
│   ├── input.h
│   ├── prompt.h
│   ├── shell.h
│   └── tokenizer.h
└── src
    ├── builtins
    │   ├── about.c
    │   ├── builtins.c
    │   ├── cd.c
    │   ├── count.c
    │   └── help.c
    ├── executor.c
    ├── input.c
    ├── main.c
    ├── prompt.c
    └── tokenizer.c
```

## 🐧Running the Shell
Follow these steps to compile and run the shell:

### 1️⃣ Clone the repository
```
https://github.com/MohamedFouad71/linux-shell.git
```
```
cd linux-shell
```
### 2️⃣ Compile the project

If you are not using Makefile:
```
gcc src/*.c src/builtins/*.c -o shell
```

If you have a Makefile:
```
make
```
### 3️⃣ Run the shell
```
./shell
```
You should see a prompt like:

```
>username@hostname:/current/directory$
```
### 4️⃣ Built-in commands

`cd <path>` → change directory

`help` → show help

`about` → info about the shell

`count <filename>` → count lines, words, and characters in a file

`exit` → exit the shell

### 5️⃣ Notes

- [x] You can also run any external Linux command like ls, grep, cat, etc.

- [x] Supports piping (|) and I/O redirection (>, >>, <).

## 👨‍💻 Contributors

- Kareem Hany
- Muhammed Fouad
- Muhammed Ashraf
- Muhammed Fatooh
- Yehya Hamdy
- Ahmed Abdullatif
- Somia Khaled