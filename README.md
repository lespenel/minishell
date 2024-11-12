# Minishell

**Minishell** is a custom, minimalistic shell built in C, inspired by Unix’s original shells like Bash. This project introduces core shell functionalities, custom command handling, and an interactive interface, helping you delve into low-level programming concepts like process management, signals, and file descriptors. Along with the mandatory requirements, this project includes advanced features and bonus implementations to enrich the shell’s capabilities.

<img width="250" height="250" src="./minishell.png">

## Features
### Core Shell Capabilities

- **Prompt and Command Input**: Displays a prompt and waits for user input. History is managed using the `readline` library.
- **Command Execution**: Supports command search and execution based on the `PATH` environment variable. Both relative and absolute paths are supported.
- **Signal Handling**: Handles signals as in Bash for a smooth interactive experience:
  - **Ctrl-C**: Cancels the current command, returning to a new prompt.
  - **Ctrl-D**: Closes the shell session.
  - **Ctrl-\\**: Ignored, as in Bash.
- **Exit Status Expansion**: `$?` expands to the exit status of the last foreground command.
- **Environment Variables**: Supports expansion of environment variables (`$VAR`) and dynamic management with the `export` and `unset` builtins.
- **Redirections**: Implements common I/O redirection:
  - `<` for input redirection
  - `>` for output redirection
  - `<<` (heredoc) to take input until a specified delimiter is encountered
  - `>>` for appending output
- **Pipes**: Full support for piping (`|`) between commands, connecting the output of one command to the input of the next.
- **Quote Handling**:
  - **Single Quotes (`'`)**: Treats content as literal, ignoring special characters.
  - **Double Quotes (`"`)**: Expands variables but treats other characters as literal.

### Builtin Commands

The following builtins are implemented to match standard shell functionality:

| Command | Description                        |
| ------- | ---------------------------------- |
| `echo`  | Prints arguments to the standard output, with `-n` option to omit trailing newline. |
| `cd`    | Changes the current directory. Supports POSIX-compliant behavior for paths. |
| `pwd`   | Prints the current working directory. |
| `export`| Sets environment variables. No additional options required. |
| `unset` | Removes specified environment variables. |
| `env`   | Displays the current environment variables. |
| `exit`  | Exits the shell. Accepts an optional exit status. |

### Bonus Features

In addition to the core requirements, several bonus features are implemented:
- **Logical Operators**: Support for `&&` and `||` operators with parenthesis for precedence, enabling complex command sequences.
- **Extended Wildcards**: Supports `*` for wildcard matching across the current directory, extended to allow recursive matches through the file structure.
- **Tilde Expansion**: Expands `~` to the user’s home directory.
- **IFS (Internal Field Separator)**: Handles custom field separation as defined in the IFS variable, allowing for custom tokenization of input.
- **POSIX `cd` Compliance**: The `cd` command is POSIX-compliant, handling standard options and edge cases as specified in the POSIX `cd` manual.
- **Subshell Support**: Commands enclosed in parentheses are treated as subshells, allowing for isolated command execution.
- **Git Branch in Prompt**: Displays the current Git branch in the prompt, enhancing the interactive experience for users in development environments.


## Credits

- [Charlie Couble](https://github.com/c-couble)
- [Léo Espenel](https://github.com/lespenel)
