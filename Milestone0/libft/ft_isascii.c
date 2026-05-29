/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acano-kr <acano-kr@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 21:08:31 by acano-kr          #+#    #+#             */
/*   Updated: 2026/04/10 21:08:31 by acano-kr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
		return (1);
	return (0);
}

/* #include <stdio.h>

int	main(void)
{
	int a = 'a';
	int b = 'A';
	int c = '\n';
	int d = ' ';
	int e = 0x80;

	printf("%d\n", ft_isascii(a));
	printf("%d\n", ft_isascii(b));
	printf("%d\n", ft_isascii(c));
	printf("%d\n", ft_isascii(d));
	printf("%d\n", ft_isascii(e));
} */
