/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_phex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acano-kr <acano-kr@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 09:29:03 by acano-kr          #+#    #+#             */
/*   Updated: 2026/04/28 08:16:41 by acano-kr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_hex(unsigned long int n, int upper)
{
	char	*base;
	int		cont;

	cont = 0;
	if (upper)
		base = "0123456789ABCDEF";
	else
		base = "0123456789abcdef";
	if (n > 15)
		cont += ft_print_hex((n / 16), upper);
	cont += ft_print_char(base[n % 16]);
	return (cont);
}

int	ft_print_ptr(void *ptr)
{
	int				cont;
	unsigned long	pointer;

	cont = 0;
	if (!ptr)
		return (ft_print_str("(nil)"));
	cont += ft_print_str("0x");
	pointer = (unsigned long)ptr;
	cont += ft_print_hex(pointer, 0);
	return (cont);
}
