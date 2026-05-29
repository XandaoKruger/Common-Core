*This project has been created as part of the 42 curriculum by acano-kr.*

## Description

This is my inaugural project at 42 School, involving the implementation of over 20 functions. The project is designed to master the fundamentals of C and the concise application of each function, establishing a critical foundation for long-term proficiency in the language.


# Libft — Functions Reference

## Part 1 — Character Classification Functions

| Function | Prototype | Description |
|----------|-----------|-------------|
| `ft_isalpha` | `int ft_isalpha(int c)` | Function that verifies if the parameter is an alphabetic character. Returns 1 if true, 0 otherwise. |
| `ft_isdigit` | `int ft_isdigit(int c)` | Function that verifies if the parameter is a digit. Returns 1 if true, 0 otherwise. |
| `ft_isalnum` | `int ft_isalnum(int c)` | Function that verifies if the parameter is alphanumeric. Returns 1 if true, 0 otherwise. |
| `ft_isascii` | `int ft_isascii(int c)` | Function that verifies if the parameter is an ASCII character. Returns 1 if true, 0 otherwise. |
| `ft_isprint` | `int ft_isprint(int c)` | Function that verifies if the parameter is a printable character. Returns 1 if true, 0 otherwise. |

## Part 1 — To Functions

| Function | Prototype | Description |
|----------|-----------|-------------|
| `ft_toupper` | `int ft_toupper(int c)` | Function that converts the parameter to uppercase if it is a lowercase letter. |
| `ft_tolower` | `int ft_tolower(int c)` | Function that converts the parameter to lowercase if it is an uppercase letter. |

## Part 1 — String Functions

| Function | Prototype | Description |
|----------|-----------|-------------|
| `ft_strlen` | `size_t ft_strlen(const char *str)` | Function that receives a string and counts the number of characters, returning the size without including the null character. |
| `ft_strchr` | `char *ft_strchr(const char *str, int ch)` | Function that receives a string and a character, and returns the substring starting from the first occurrence of the character until the end of the string. |
| `ft_strrchr` | `char *ft_strrchr(const char *str, int chr)` | Searches for the last occurrence of `chr` in `str`. Returns a pointer to the match or `NULL` if not found. |
| `ft_strncmp` | `int ft_strncmp(const char *str, const char *st, size_t count)` | Function that compares two strings up to `count` characters, returning the difference between them. Returns a negative number if `st` is larger than `str`. |
| `ft_strlcpy` | `size_t ft_strlcpy(char *dest, const char *src, size_t size)` | Copies up to `size-1` characters from `src` to `dest` and adds a null terminator. |
| `ft_strlcat` | `size_t ft_strlcat(char *dest, const char *src, size_t size)` | Concatenates `src` to the end of `dest` up to `size` bytes total, adding a null terminator. Returns the length the string would have had if there was enough space. If buffer has space: `return len_src + len_dest`. If buffer too small: `return size + len_src`. |
| `ft_strnstr` | `char *ft_strnstr(const char *str, const char *src, size_t size)` | Searches for the first occurrence of `src` in `str` within the first `size` characters. Returns a pointer to the match or `NULL` if not found. |
| `ft_atoi` | `int ft_atoi(const char *str)` | Function that converts a string to an integer. Stops conversion when encountering non-digit characters after the initial number sequence. Does not perform conversion if there is more than one sign character. |
| `ft_bzero` | `void ft_bzero(void *str, size_t n)` | Function that sets `n` bytes of the given void pointer to the null character. |
| `ft_memset` | `void ft_memset(void *dest, int ch, size_t count)` | Function that sets `count` bytes of `dest` to the character `ch`. |
| `ft_memcpy` | `void *ft_memcpy(void *dest, const void *src, size_t count)` | Function that copies data from one void pointer to another, byte by byte, up to the specified size. |
| `ft_memmove` | `void *ft_memmove(void *dest_str, const void *src_str, size_t numBytes)` | Function that copies `numBytes` from `src_str` to `dest_str`, handling overlapping memory safely by copying forwards or backwards as needed. |
| `ft_memchr` | `void *ft_memchr(const void *str, int chr, size_t size)` | Searches for the first occurrence of `chr` in `void *str` until `size_t size` bytes of a block of memory. Returns a pointer to the match or `NULL` if not found. |
| `ft_memcmp` | `int ft_memcmp(const void *s1, const void *s2, size_t size)` | This function will compare two `void *` pointer `s1` and `s2` until `size_t size` bytes of a block of memory. Returns 0 if they are equal, a positive number if `s1` is bigger than `s2` and a negative number if `s1` is smaller than `s2`. |
| `ft_calloc` | `void *ft_calloc(size_t space, size_t size)` | This function allocates an amount of memory `size_t space` of a type of the data you want to pass `size_t size` and fills it with 0 and returns a pointer to it. |
| `ft_strdup` | `char *ft_strdup(const char *src)` | This function will receive `const char *src` and will store the equal size of memory, copy the string and return a pointer that will be the copy of the `const char *src`. |

## Part 2 — Additional Functions

| Function | Prototype | Description |
|----------|-----------|-------------|
| `ft_substr` | `char *ft_substr(const char *s, unsigned int start, size_t end)` | This function will receive `const char *str` and will create a substring of the string, from the `size_t start` until the `size_t end` and will return the new string. |
| `ft_strjoin` | `char *ft_strjoin(char const *s1, char const *s2)` | This function will receive `const char *s1` and `const char *s2`, will create a new string, it will literally join both strings in a new one, and will return the pointer to the new string. |
| `ft_strtrim` | `char *ft_strtrim(char const *s1, char const *set)` | Returns a copy of `s1` with the characters from `set` removed from the beginning and the end. |
| `ft_split` | `char **ft_split(char const *str, char c)` | This function will receive `char const *s1` and `char set`, and will create a 2d array, counting the words by the `char set` delimiter. If just one of the allocations of new strings to the array fails it will free all the array, and return `NULL`. |
| `ft_itoa` | `char *ft_itoa(int number)` | This function will receive `int number` and convert it to a string and return a string. If something fails will return `NULL`. |
| `ft_strmapi` | `char *ft_strmapi(char const *s, char (*f)(unsigned int, char))` | Applies the function `f` to each character of the string `s`, passing its index as the first argument and the character itself as the second. A new string is created (using malloc(3)) to store the results from the successive applications of `f`. |
| `ft_striteri` | `void ft_striteri(char *s, void (*f)(unsigned int, char*))` | Applies the function `f` to each character of the string passed as argument, passing its index as the first argument. Each character is passed by address to `f` so it can be modified if necessary. |

## Part 2 — Write Functions

| Function | Prototype | Description |
|----------|-----------|-------------|
| `ft_putchar_fd` | `void ft_putchar_fd(char c, int fd)` | This function will write a character passed on `char c` on the `int fd` to the file descriptor: Standard Input (0, stdin), Standard Output (1, stdout), Standard Error (2, stderr). |
| `ft_putstr_fd` | `void ft_putstr_fd(char *s, int fd)` | This function will write an array of characters passed on `char *s` on the `int fd` to the file descriptor: Standard Input (0, stdin), Standard Output (1, stdout), Standard Error (2, stderr). |
| `ft_putendl_fd` | `void ft_putendl_fd(char *s, int fd)` | This function will write an array of characters passed on `char *s` on the `int fd` to the file descriptor and write a new line character `\n`: Standard Input (0, stdin), Standard Output (1, stdout), Standard Error (2, stderr). |
| `ft_putnbr_fd` | `void ft_putnbr_fd(int n, int fd)` | This function will write numbers passed on `int n` on the `int fd` to the file descriptor: Standard Input (0, stdin), Standard Output (1, stdout), Standard Error (2, stderr). |

## Part 3 — Linked List Functions

### The struct

```c
typedef struct s_list
{
    void          *content;
    struct s_list *next;
}   t_list;
```

Linked list is a linear data structure made of nodes connected using pointers. Each node has: `content`: The value stored in the node. `next`: A reference to the next node. **Struct**: It's like a mold that groups related variables, like a database. **typedef**: It is used to create an alias for a data type; instead of writing a struct s_list, we simply write t_list.

| Function | Prototype | Description |
|----------|-----------|-------------|
| `ft_lstnew` | `t_list *ft_lstnew(void *content)` | This function creates a new list, and receives a `void *content` and the list receives the passed content, and points to NULL. |
| `ft_lstadd_front` | `void ft_lstadd_front(t_list **lst, t_list *new)` | This function lets us add a new element to the front of an existing list. `t_list **lst`: pointer address to the first element of the list. `*new`: pointer address of the new element to add to the list. |
| `ft_lstsize` | `int ft_lstsize(t_list *lst)` | This function counts the amount of lists that we have on our linked-list. |
| `ft_lstlast` | `t_list *ft_lstlast(t_list *lst)` | This function will iterate through the linked list and return the last list of the linked list. |
| `ft_lstadd_back` | `void ft_lstadd_back(t_list **lst, t_list *new)` | This function adds a new node to the end of a linked list. It ensures the new node becomes the last element, properly updating the pointer of the previous last node to point to the new node, handling empty lists by setting the head to the new node. |
| `ft_lstdelone` | `void ft_lstdelone(t_list *lst, void (*del)(void*))` | The function ft_lstdelone deletes the content of a list node with the function passed as parameter before freeing the memory of the node. |
| `ft_lstclear` | `void ft_lstclear(t_list **lst, void (*del)(void*))` | Deletes and frees the given node and all its successors, using the function 'del' and free(3). Finally, set the pointer to the list to NULL. |
| `ft_lstiter` | `void ft_lstiter(t_list *lst, void (*f)(void *))` | This function applies the passed function `void (*f)(void *)` to each content of the lists on the linked list. |
| `ft_lstmap` | `t_list *ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))` | Iterate over the list 'lst' and apply the function 'f' to the content of each element. Create a new list resulting of the successive applications of 'f'. The function 'del' is used to destroy the content of an element if necessary. |

<hr>
<h2>Instructions</h2>

<p>Navigate to the directory containing the source files and the Makefile. Execute the make command to compile the library; this will produce the libft.a archive. To utilize the library in your projects, link this binary during the compilation of your source files.</p>

>To compile the library:
> __make__

>To compile your project using libft:
> __cc -Wall -Wextra -Werror main.c -L. -lft -o program_name__

<h2>Resources</h2>
<p>I leveraged Artificial Intelligence to dissect each function's underlying logic, facilitating an in-depth understanding of control flows and execution patterns. This approach allowed for a comprehensive mental mapping of function mechanics beyond mere implementation.</p>