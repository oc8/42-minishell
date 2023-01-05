# Minishell

Minishell is a project from 42 school consisting in coding a simple Unix shell in C.

## Features

Minishell must be able to handle the following basic commands:

- Execution of external programs (for example, `ls`, `cat`, `echo`, etc.) with their arguments
- Handling of redirection operators (`>`, `>>`, `<`, `|`)
- Execution of commands in the background with `&`
- Handling of builtins `cd`, `echo`, `setenv`, `unsetenv`, `env`, `exit`

Minishell must also handle the `SIGINT` (Ctrl + C) and `SIGQUIT` (Ctrl + \\) signal handlers.

## Usage

To use Minishell, compile the program using the `make` command and then run it with `./minishell`. You can then enter commands in the shell as in any other Unix shell.
