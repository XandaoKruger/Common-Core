/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acano-kr <acano-kr@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 18:21:57 by acano-kr          #+#    #+#             */
/*   Updated: 2026/04/14 18:21:57 by acano-kr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dsize)
{
	size_t	ld;
	size_t	ls;
	size_t	i;

	ld = ft_strlen(dst);
	ls = ft_strlen(src);
	if (dsize <= ld)
		return (dsize + ls);
	i = 0;
	while (src[i] && (ld + i + 1) < dsize)
	{
		dst[ld + i] = src[i];
		i++;
	}
	dst[ld + i] = '\0';
	return (ld + ls);
}
/* 
#include <stdio.h>

int	main(void)
{
	char a[20] = "Ultimis";
	char b[] = "Primis";
	unsigned int c = 20;

	printf("%ld\n", ft_strlcat(a, b, c));
	printf("%s\n", a);
} */
