/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pnbr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acano-kr <acano-kr@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/26 22:05:28 by acano-kr          #+#    #+#             */
/*   Updated: 2026/04/26 22:05:28 by acano-kr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

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
