*This project has been created as part of the 42 curriculum by mmittelb, jnieders.*

# cub3d
## Description

**At a high level, our project provides the following features:**

<br>

## Mandatory Features

<br>

## Bonus Features

<br>

## Memory management (GC)
The project uses a custom garbage collection mechanism to manage dynamic memory allocations.  
All allocations are tracked centrally and freed at well-defined points in the program lifecycle, which simplifies error handling and prevents memory leaks across complex execution paths (parsing, execution, heredocs, and signal handling).  

<br>

## Instructions

**A Unix-like environment (Linux or macOS) is required to build and run this project.**
- `make`
- A *"C"* compiler (`cc`, `clang`, or `gcc`)
- Readline development headers (depending on your setup)
<br>

### Build
Compile the project with:
```bash
make
```
Optional build targets:
```bash
make clean
make fclean
make re
```

### Run
```bash
./cub3D
```

### Usage examples
```bash

...

```

### Notes on behavior

- **ctrl-D** 
- **ctrl-C** 
- **ctrl-\\** 
<br>

## Project structure

```text

?????

.
├── Makefile
├── include/
│   ├── minishell.h
│   ├── parse.h
│   ├── exec.h
│   ├── env.h
│   ├── expansions.h
│   ├── gc.h
│   └── utils.h
└── src/
    ├── main.c
    ├── parser/
    │   ├── parse.c
    │   ├── parse_helpers.c
    │   ├── handle_missing_token.c
    │   ├── redirections/
    │   └── expansions/
    ├── exec/
    │   ├── exec.c
    │   ├── exec_cmd.c
    │   ├── exec_pipe.c
    │   ├── exec_redir.c
    │   ├── collect_heredocs.c
    │   ├── exec_heredoc.c
    │   └── builtins/
    ├── env/
    ├── gc/
    ├── libft/
    ├── error_handling/
    └── utils/
```
<br>

### Resources
The following resources were used as primary references throughout the development of this project:


<br>

### Use of AI
AI tools were used as a **supporting resource** during the development of this project.  
They were primarily used to:
- clarify theoretical background and expected shell behavior,
- discuss edge cases and ambiguities in the subject,
- assist with documentation wording and structure.

AI was **not used to directly generate or copy complete implementations** of the project’s core logic. All code was written and integrated by the project authors.
