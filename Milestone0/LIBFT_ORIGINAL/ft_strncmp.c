/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acano-kr <acano-kr@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 21:56:04 by acano-kr          #+#    #+#             */
/*   Updated: 2026/04/12 21:56:04 by acano-kr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (i < n - 1 && (unsigned char)s1[i] == (unsigned char)s2[i]
		&& s1[i] != '\0' && s2[i] != '\0')
		i++;
	if (i == n)
		return (0);
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

/* #include <stdio.h>

int	main(void)
{
	char a[] = "abc"; // Esse teste verifica a integridade do n-ésimo caractere,
						// ou seja, ele verifica o último; 
						// no caso n - 1 no loop, ou i = 1, 
						// causariam essa brecha que foi considerada na piscine.
	char b[] = "abd";

	printf("%d\n", ft_strncmp(a, b, 3));
} */
