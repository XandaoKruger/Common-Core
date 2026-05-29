/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acano-kr <acano-kr@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 02:44:45 by acano-kr          #+#    #+#             */
/*   Updated: 2026/04/11 02:44:45 by acano-kr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_tolower(int c)
{
	if (c >= 65 && c <= 90)
	{
		c = c + 32;
		return (c);
	}
	return (c);
}

/* #include <stdio.h>

int	main(void)
{
	int a = 'G';

	printf("O valor da letra em ASCII: %d\n", ft_tolower(a));
	printf("A letra representante em minúscula: %c\n", ft_tolower(a));
} */
