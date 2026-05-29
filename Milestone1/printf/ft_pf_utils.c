/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pf_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acano-kr <acano-kr@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 11:41:04 by acano-kr          #+#    #+#             */
/*   Updated: 2026/05/15 12:00:21 by acano-kr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

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
