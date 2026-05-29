/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acano-kr <acano-kr@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 22:53:54 by acano-kr          #+#    #+#             */
/*   Updated: 2026/05/18 22:53:54 by acano-kr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_char(const char c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_print_specs(char x, va_list args)
{
	if (x == 'c')
		return (ft_print_char(va_arg(args, int)));
	else if (x == 's')
		return (ft_print_str(va_arg(args, char *)));
	else if (x == 'd' || x == 'i')
		return (ft_print_nbr(va_arg(args, int)));
	else if (x == 'u')
		return (ft_print_uns_nbr(va_arg(args, unsigned int)));
	else if (x == 'x')
		return (ft_print_hex(va_arg(args, unsigned int), 0));
	else if (x == 'X')
		return (ft_print_hex(va_arg(args, unsigned int), 1));
	else if (x == 'p')
		return (ft_print_ptr(va_arg(args, void *)));
	else
		return (0);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		i;
	int		cont;

	if (!format)
		return (-1);
	va_start(args, format);
	i = 0;
	cont = 0;
	while (format[i])
	{
		if (format[i] == '%')
		{
			i++;
			if (format[i] == '%')
				cont += ft_print_char('%');
			else
				cont += ft_print_specs(format[i], args);
		}
		else
			cont += ft_print_char(format[i]);
		i++;
	}
	va_end(args);
	return (cont);
}
