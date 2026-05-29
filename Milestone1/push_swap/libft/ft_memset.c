/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acano-kr <acano-kr@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 21:03:25 by acano-kr          #+#    #+#             */
/*   Updated: 2026/04/13 21:03:25 by acano-kr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*ptr;

	ptr = (unsigned char *)s;
	while (n)
	{
		if (n > 0)
		{
			*ptr = (unsigned char)c;
			ptr++;
			n--;
		}
	}
	return (s);
}

/* #include <stdio.h>

int main(void)
{
	char	ptr[] = "Nuketown";
	int	a = 'X';
	char	*str;
	unsigned int	b = 4;

	str = ft_memset(ptr, a, b);
	printf("%s\n", str);

	unsigned int	c = 8;
	
	str = ft_memset(ptr, a, c);
	printf("%s\n", str);
	return (0);
} */
