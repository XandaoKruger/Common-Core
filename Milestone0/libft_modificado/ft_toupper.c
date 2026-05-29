/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acano-kr <acano-kr@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 02:12:10 by acano-kr          #+#    #+#             */
/*   Updated: 2026/04/11 02:12:10 by acano-kr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_toupper(int c)
{
	if (c >= 97 && c <= 122)
	{
		c = c - 32;
		return (c);
	}
	return (c);
}

/* #include <stdio.h>

int	main(void)
{
	int a = 'g';

	printf("O valor da letra em ASCII: %d\n", ft_toupper(a));
	printf("A letra representante em maiuscula: %c\n", ft_toupper(a));
} */