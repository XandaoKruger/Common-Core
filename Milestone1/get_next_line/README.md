*This project has been created as part of the 42 curriculum by acano-kr.*

---

# Get Next Line

## Description

`get_next_line` is a C function that reads and returns one line at a time from a file descriptor. Each call returns the next line, including the terminating `\n` character — except when the end of file is reached without a `\n`. Returns `NULL` when there is nothing left to read or an error occurs.

The core concept behind this project is the **static variable** — a variable that persists between function calls, used here to store leftover data between reads.

---

## Files

```
get_next_line.c       — main function
get_next_line_utils.c — helper functions (ft_strdup, ft_strjoin, 
						ft_strchr, ft_substr, ft_strlen)
get_next_line.h       — prototypes and BUFFER_SIZE definition
```

---

## Instructions

Compile with the `-D BUFFER_SIZE=n` flag to define the read buffer size:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c
```

If no flag is provided, the default `BUFFER_SIZE` defined in the header is used.

Usage example:

```c
int     fd;
char    *line;

fd = open("file.txt", O_RDONLY);
while ((line = get_next_line(fd)) != NULL)
{
    printf("%s", line);
    free(line);
}
close(fd);
```

---

## Algorithm

The function is split into three stages:

**1. `read_until`** — reads from the file descriptor and accumulates data into a static remainder string until a `\n` is found or EOF is reached. Uses a temporary pointer to free the previous remainder before each `ft_strjoin`, preventing memory leaks.

**2. `extr_line`** — extracts the first line from the remainder (from start to `\n` inclusive) using `ft_substr`. If no `\n` exists, returns whatever remains — handling the last line of a file without a terminating newline.

**3. `updt_reminder`** — updates the static remainder by discarding the extracted line and keeping only what comes after the `\n`, ready for the next call.

The static variable `reminder` lives in the Data segment of memory — not the stack — so it persists across calls without being destroyed when the function returns.

---

## Resources

- `man 2 read` — read system call documentation
- `man 3 malloc` / `man 3 free` — memory management
- [Static variables in C — GeeksForGeeks](https://www.geeksforgeeks.org/static-variables-in-c/)

**AI usage:** Claude was used to explain concepts (static variables, memory zones, read behaviour) and to guide debugging of memory leaks. All code was written and understood independently.

---

## Explanations and justifications

### Implementation summary
I chose to split the logic across three functions — accumulated read, line extraction, and remainder update — and to use a static variable to persist buffered content between calls. This is a simple, direct solution for reading the input line-by-line without introducing external data structures.

### Memory management
All temporary allocations are explicitly freed on both success and error paths.
The returned string is owned by the caller and must be freed by the receiver.
### Error handling and edge cases
read() returning -1 or a failed malloc() triggers cleanup and results in NULL.
When EOF is reached but there is accumulated content, the implementation returns the final line even if it lacks a terminating '\n'.
### Testing
Manual tests include:

 - empty files,
 - files consisting of a single '\n',
 - files whose last line lacks a trailing '\n',
 - lines longer than BUFFER_SIZE.

I use Valgrind to ensure zero memory leaks on normal paths.

```zsh
valgrind --leak-check=full
```

### Limitations and possible improvements
 - The implementation is not thread-safe because it uses a static buffer scoped per file descriptor.
 - Very long lines may cause frequent reallocations.

Plausible improvements: maintain per-FD buffers or adopt a circular buffer strategy to reduce reallocations and improve concurrency.