/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acano-kr <acano-kr@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 13:16:34 by acano-kr          #+#    #+#             */
/*   Updated: 2026/04/28 11:12:55 by acano-kr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*ptrd;
	unsigned char	*ptrs;

	ptrd = (unsigned char *)dest;
	ptrs = (unsigned char *)src;
	if (ptrd == ptrs || n == 0)
		return (dest);
	if (dest <= src)
		while (n--)
			*ptrd++ = *ptrs++;
	else
		while (n--)
			ptrd[n] = ptrs[n];
	return (dest);
}
/* #include <stdio.h>

int	main(void)
{
	char	a[] = "Nuketown";
	char	b[] = "nwotekuN";
	size_t	d = 8;

	ft_memmove(a, b, d);
	printf("%s\n", a);
} */
