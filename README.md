# minishell_stable (42 Minishell)

A **minimal Unix shell** written in C as part of the **42 “minishell”** project: parse a command line, handle quoting/expansions, and execute commands with pipes/redirections while matching the expected Bash-like behavior for the project scope. :contentReference[oaicite:0]{index=0}

---

## Features

Implemented to match the Minishell subject expectations (Bash-like behavior, not full POSIX):

- Interactive prompt (readline-style UX)
- Execute binaries from `$PATH` or via absolute/relative paths
- **Pipes**: `cmd1 | cmd2 | cmd3`
- **Redirections**: `>`, `>>`, `<`, `<<` (heredoc)
- **Quotes**: single `'` and double `"` (with proper parsing rules)
- **Environment expansion**: `$VAR` and `$?`
- **Signals**: typical interactive handling for `Ctrl-C`, `Ctrl-D`, `Ctrl-\`
- **Builtins** (project set): `echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`

> Note: exact edge-case coverage depends on your implementation choices, but this README is structured for a standard 42 Minishell deliverable.

---

## Repository layout

- `src/` — project source code :contentReference[oaicite:1]{index=1}  
- `includes/` — headers :contentReference[oaicite:2]{index=2}  
- `libft/` — embedded libft dependency :contentReference[oaicite:3]{index=3}  
- `Makefile` — build rules :contentReference[oaicite:4]{index=4}  
- `suppression.vg` — Valgrind suppression file (useful with readline leaks) :contentReference[oaicite:5]{index=5}  
- `make_graph.sh` — helper script (likely for visualization/debug tooling) :contentReference[oaicite:6]{index=6}  
- `ascii/` — assets (banner/art) :contentReference[oaicite:7]{index=7}  

Language breakdown: mostly **C**. :contentReference[oaicite:8]{index=8}

---

## Build & run

### Requirements
- A Unix-like environment (Linux/macOS)
- `make`
- A compiler (typically `cc` / `clang`)
- `readline` installed (common minishell dependency)

### Compile
```sh
make

Run

./minishell

Clean

make clean      # objects
make fclean     # objects + binary
make re         # full rebuild

Usage examples

minishell$ echo "hello world"
minishell$ export FOO=bar
minishell$ echo $FOO
minishell$ ls -la | grep minishell
minishell$ cat < infile | wc -l > out.txt
minishell$ cat << EOF
heredoc line 1
heredoc line 2
EOF
minishell$ echo $?
```
### Debugging
Valgrind (recommended)

Readline often reports “leaks” that are not yours; suppress them using the repository suppression file:

valgrind --leak-check=full \
         --show-leak-kinds=all \
         --track-origins=yes \
         --track-fds=yes \
         --suppressions=suppression.vg \
         ./minishell

File descriptor sanity

A classic Minishell bug is leaking FDs across pipelines/redirections. Tools like:

lsof -p <pid>

valgrind --track-fds=yes

help catch it early.
