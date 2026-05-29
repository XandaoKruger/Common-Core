/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acano-kr <acano-kr@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 22:51:13 by acano-kr          #+#    #+#             */
/*   Updated: 2026/05/18 22:51:13 by acano-kr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_str(const char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (ft_print_str("(null)"));
	while (s[i])
	{
		ft_print_char(s[i]);
		i++;
	}
	return (i);
}

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

int	ft_print_nbr(long n)
{
	int	cont;

	cont = 0;
	if (n < 0)
	{
		cont += ft_print_char('-');
		n = -n;
	}
	if (n > 9)
		cont += ft_print_nbr(n / 10);
	cont += ft_print_char((n % 10) + '0');
	return (cont);
}

int	ft_print_uns_nbr(unsigned long int n)
{
	int	i;

	i = 0;
	if (n > 9)
		i += ft_print_uns_nbr(n / 10);
	i += ft_print_char((n % 10) + '0');
	return (i);
}
