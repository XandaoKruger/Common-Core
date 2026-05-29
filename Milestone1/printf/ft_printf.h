/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acano-kr <acano-kr@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 12:24:55 by acano-kr          #+#    #+#             */
/*   Updated: 2026/04/28 08:00:10 by acano-kr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <limits.h>
# include <stdlib.h>
# include <stdarg.h>

int	ft_printf(const char *format, ...);
int	ft_print_char(const char c);
int	ft_print_str(const char *s);
int	ft_print_nbr(long int n);
int	ft_print_uns_nbr(unsigned long int n);
int	ft_print_hex(unsigned long int n, int upper);
int	ft_print_ptr(void *ptr);
int	ft_print_specs(char x, va_list args);

#endif