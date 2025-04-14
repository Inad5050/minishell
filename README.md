# Minishell

A simple Unix shell implementation developed as part of the 42 curriculum. This project aims to replicate the basic functionality of a shell while introducing key features such as job control and command parsing.

---

## Features

- Command execution (e.g., `ls`, `echo`, etc.)
- Built-in commands: `cd`, `export`, `unset`, `env`, `exit`, etc.
- Environment variable management
- Pipes (`|`) and redirections (`>`, `<`, `>>`)
- Signal handling (e.g., `Ctrl+C`, `Ctrl+D`, `Ctrl+\`)
- Error handling with custom messages
- Input parsing, quoting (`'`, `"`), and escaping (`\`)

---


## Getting Started

### Prerequisites

- A Unix-based operating system (Linux or macOS)
- GCC compiler
- GNU Make
---
### Installation

1. Clone the repository:
   ```bash
   git clone git@github.com:otboumeh/Minishell.git
   cd minishell
2. Compile the project:

  ```bash
   make
```
3. Run the shell:

```bash
   ./minishell
```
---
### Usage
   a. Execute standard Unix commands:

```bash
   ls -la
```
  b. Use built-in commands:

```bash
 export VAR=value
```
```bash
   echo $VAR
```
   c. Chain commands with pipes:

```bash
   ls | grep txt
```
   d. Redirect input/output:

```bash
   echo "Hello, world!" > file.txt
```
```bash
   cat < file.txt
```
---
## Built-in Commands

Minishell supports several built-in commands to manage the shell environment:

- `cd [directory]`: Changes the current working directory.
  - Example: 
    ```bash
     cd /path/to/directory
    ```

- `export [VAR=value]`: Sets or updates environment variables.
  - Example: 
    ```bash
     export MY_VAR=hello
     echo $MY_VAR
    hello
    ```

- `unset [VAR]`: Removes an environment variable.
  - Example: 
    ```bash
    unset MY_VAR
    ```

- `env`: Displays all environment variables.
  - Example: 
    ```bash
    env
    ```

- `exit`: Exits the shell.
  - Example:
    ```bash
    exit
    ```

---
## File Structure

- `src/`: Source files
  - `main.c`: Entry point for the shell
  - `parser.c`: Handles input parsing and tokenization
  - `execution.c`: Executes commands
- `include/`: Header files
- `Makefile`: Build instructions

---

## Known Limitations

- Limited support for some advanced shell features.
- Background jobs (`&`) not yet implemented.

---

## Future Improvements

- Add support for background processes.
- Enhance error reporting.
- Improve input parsing for edge cases.
---
## Authors

- **otboumeh** ([GitHub Profile](https://github.com/otboumeh))
- **inad5050** ([GitHub Profile](https://github.com/inad5050))
