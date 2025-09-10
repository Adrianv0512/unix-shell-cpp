# Mini Unix Shell (C++)

A minimal Unix shell written in C++ supporting built-in commands (`cd`, `exit`) and external program execution using `fork`, `execvp`, and `waitpid`. Built as a systems programming project to explore how shells manage processes.

---

## Features
- Custom shell prompt (`$`)
- Built-ins:
  - `cd [dir]` → change directory
  - `exit` → exit shell
- Launch any external program in `$PATH`
- Error handling with `errno` + `strerror`

---

## Planned Features

I/O redirection (<, >, >>)

Pipes (|)

Background jobs (&)

Command history

---

## Build & Run

```bash
Build
make

Run
./minishell




