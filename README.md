# 🐧 Linux Shell  
A simple Linux-like shell written in C for learning OS concepts, system calls, and command execution.

## 🚀 Overview
This project is a simple terminal, similar to a Linux shell, built to help us learn the core fundamentals of how shells work.
It covers essential concepts such as:
- Parsing  
- Tokenization  
- Process creation (fork)  
- Command execution (execvp)  
- Built-in commands  
- I/O Redirection (dub2)
- Piping (pipe)
- logical or
- History  
- Colored prompt  

## 📁 Project Structure

```
.
├── Makefile
├── README.md
├── data
│   └── cmd_history
├── include
│   ├── builtins.h
│   ├── cmdHistory.h
│   ├── executor.h
│   ├── input.h
│   ├── pipeline
│   │   ├── pipe_detector.h
│   │   ├── pipe_executer.h
│   │   └── logical_or.h
│   ├── pipeline.h
│   ├── prompt.h
│   ├── redirection
│   │   ├── input_redirection.h
│   │   ├── redirect_detector.h
│   │   ├── redirect_executor.h
│   │   └── redirect_helper.h
│   ├── redirection_append.h
│   ├── shell.h
│   ├── tokenizer.h
│   └── trim.h
└── src
    ├── builtins
    │   ├── about.c
    │   ├── builtins.c
    │   ├── cd.c
    │   ├── cmdHistory.c
    │   ├── count.c
    │   └── help.c
    ├── executor.c
    ├── input.c
    ├── main.c
    ├── pipeline
    │   ├── pipe_detector.c
    │   ├── pipe_executer.c
    │   └── logical_or.c
    ├── prompt.c
    ├── redirection
    │   ├── input_redirection.c
    │   ├── redirect_detector.c
    │   ├── redirect_executor.c
    │   └── redirect_helper.c
    ├── tokenizer.c
    └── trim.c
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
gcc src/*.c src/builtins/*.c src/redirection/*.c src/pipeline/*.c -o shell -lreadline
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
username@hostname:/current/directory$
```
---
> You can compile and run the project using `make run`.  

> To remove object files and executables, use `make clean`.
---
### 4️⃣ Built-in commands

| Command           | Description                         |
|------------------|-------------------------------------|
| `cd <path>`       | Change directory                    |
| `help`            | Show help                            |
| `about`           | Info about the shell                |
| `count <file>`    | Count lines, words, and characters |
| `exit`            | Exit the shell                      |

---

### 5️⃣ Notes

- [x] Supports external Linux commands (`ls`, `grep`, `cat`, etc.)

- [x] Supports piping `|` and all I/O redirection types (`>`, `>>`, `<`, `<<`, `2>`, `2>>`, `&>`, `&>>`)


## 👨‍💻 Contributors

- Kareem Hany
- Muhammed Fouad
- Muhammed Ashraf
- Muhammed Fatooh
- Yehya Hamdy
- Ahmed Abdullatif
- Somia Khaled
