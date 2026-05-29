/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pchar.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acano-kr <acano-kr@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/26 17:46:16 by acano-kr          #+#    #+#             */
/*   Updated: 2026/04/26 17:46:16 by acano-kr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_char(const char c)
{
	write(1, &c, 1);
	return (1);
}

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
