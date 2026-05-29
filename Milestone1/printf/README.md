*This project has been created as part of the 42 curriculum by acano-kr.*

## Description

This project consists of creating my own implementation of the printf mechanism, as specified in man 3 printf, which served as the primary guide for developing a faithful representation of its behavior. Its purpose is to deepen my understanding of variadic functions by implementing the mandatory conversion specifiers, namely %c, %s, %p, %d, %i, %u, %x, %X, and %%.

| Conversion Specifier | Description |
|----------------------|-------------|
| %c | Prints a single character. |
| %s | Prints a string. |
| %p | Prints a pointer address in hexadecimal format. |
| %d | Prints a signed decimal integer. |
| %i | Prints a signed integer in decimal format. |
| %u | Prints an unsigned decimal integer. |
| %x | Prints an unsigned integer in lowercase hexadecimal format. |
| %X | Prints an unsigned integer in uppercase hexadecimal format. |
| %% | Prints a literal percent sign. |


## Instructions

Navigate to the project directory containing the source files and the Makefile. Execute the make command to compile the library; this will generate the libftprintf.a static archive. Link this library during compilation to integrate ft_printf into your programs.

### To compile the library:
```bash 
make 
```
### To compile a test file using ft_printf:
```bash
 cc -Wall -Wextra -Werror main.c -L. -lftprintf -o test_ft_printf 
 ```

> Note: Ensure libftprintf.a is present in the working directory. The linker option -lftprintf instructs the compiler to link against libftprintf.a, and -L. specifies the current directory as the library search path.

## Resources
I leveraged Artificial Intelligence to dissect each function's underlying logic, facilitating an in-depth understanding of control flows and execution patterns. This approach was particularly instrumental in demystifying the mechanics of variadic functions, enabling a robust grasp of how to handle indefinite arguments through the stdarg infrastructure. Ultimately, this allowed for a comprehensive mental mapping of function architecture beyond mere implementation.  
42 subject.  
man 3 printf.  
man stdarg.  

## Explanation/Justifications
The architectural approach involved modularizing basic operations into a dedicated utils file to support the primary function, ensuring strict adherence to the Norm's line limits. While the auxiliary functions mirror those in my libft, the printf requirement for an integer return value (to track byte count) necessitated a transition from void to int. Consequently, I opted to reimplement these functions locally rather than linking the previous library, prioritizing internal consistency and precise return-to-caller tracking.