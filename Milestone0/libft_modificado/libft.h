/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acano-kr <acano-kr@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 16:53:07 by acano-kr          #+#    #+#             */
/*   Updated: 2026/04/15 16:53:07 by acano-kr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

//LIBS EXTERNAS=================================================================
# include <unistd.h>
# include <stddef.h>
# include <stdlib.h>
# include <stdint.h>
# include <stdio.h>
# include <limits.h>
# include <stdarg.h>
# include <fcntl.h>
//END LIBS EXTERNAS=============================================================

// BUFFER SIZE GET NEXT LINE====================================================
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif
//END BUFFER SIZE GET NEXT LINE=================================================

//STRUCT LINKED LISTS===========================================================
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;
//END STRUCT LINKED LISTS=======================================================

//LIBFT FUNCTIONS===============================================================
int		ft_atoi(const char *str);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t count, size_t size);
int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isascii(int c);
int		ft_isdigit(int c);
int		ft_isprint(int c);
char	*ft_itoa(int n);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstadd_front(t_list **lst, t_list *new);
void	ft_lstclear(t_list **lst, void (*del)(void*));
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstlast(t_list *lst);
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
t_list	*ft_lstnew(void *content);
int		ft_lstsize(t_list *lst);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	*ft_memset(void *s, int c, size_t n);
void	ft_putchar_fd(char c, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_putstr_fd(char *s, int fd);
char	**ft_split(char const *s, char c);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *s1);
void	ft_striteri(char *s, void (*f)(unsigned int, char *));
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlcat(char *dst, const char *src, size_t dsize);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	ft_strlen(const char *s);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strnstr(const char *big, const char *litlle, size_t len);
char	*ft_strrchr(const char *s, int c);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int		ft_tolower(int c);
int		ft_toupper(int c);
//END LIBFT FUNCTIONS===========================================================

//PRINTF FUNCTIONS==============================================================
int		ft_printf(const char *format, ...);
int		ft_print_char(const char c);
int		ft_print_str(const char *s);
int		ft_print_nbr(long int n);
int		ft_print_uns_nbr(unsigned long int n);
int		ft_print_hex(unsigned long int n, int upper);
int		ft_print_ptr(void *ptr);
int		ft_print_specs(char x, va_list args);
//END PRINTF FUNCTIONS==========================================================

//GET NEXT LINE FUNCTIONS
char	*get_next_line(int fd);
char	*read_until(int fd, char *buffer, char *remi);
char	*extr_line(char *remind);
char	*updt_reminder(char *remin);
//END GET NEXT LINE FUNCTIONS

#endif