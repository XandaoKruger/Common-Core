/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acano-kr <acano-kr@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 12:13:55 by acano-kr          #+#    #+#             */
/*   Updated: 2026/05/14 15:33:38 by acano-kr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100000
# endif

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>

//---------------------------------- Main Func
char	*get_next_line(int fd);
//---------------------------------- Aux Func
char	*read_until(int fd, char *buffer, char *remi);
char	*extr_line(char *remind);
char	*updt_reminder(char *remin);
//---------------------------------- Util Func
int		ft_strlen(char *s);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strchr(char *s, int c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strdup(const char *s1);

#endif