/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acano-kr <acano-kr@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 17:11:25 by acano-kr          #+#    #+#             */
/*   Updated: 2026/05/11 11:51:41 by acano-kr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

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

/* int	main(void)
{
	int	inteiro = 42;
	char *string = "Totenreich";
	char c = 'c';
	unsigned int A = 21;
	

	ft_printf("%d\n", inteiro);
	ft_printf("%s\n", string);
	ft_printf("%i\n", inteiro);
	ft_printf("%p\n", string);
	ft_printf("%x\n", A);
	ft_printf("%X\n", A);
	ft_printf("%c\n", c);
	ft_printf("%u\n", A);
	ft_printf("%%\n");
} */
