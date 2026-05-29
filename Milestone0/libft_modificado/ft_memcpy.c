/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acano-kr <acano-kr@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 12:21:37 by acano-kr          #+#    #+#             */
/*   Updated: 2026/04/23 14:53:41 by acano-kr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*ptrd;
	unsigned char	*ptrs;

	ptrd = (unsigned char *)dest;
	ptrs = (unsigned char *)src;
	if (n == 0 || ptrd == ptrs)
		return (dest);
	while (n)
	{
		*ptrd = *ptrs;
		ptrd++;
		ptrs++;
		n--;
	}
	return (dest);
}

/* #include <stdio.h>

int	main(void)
{
	char	a[] = "Nuketown";
	char	b[] = "nwotekuN";
	size_t	d = 8;

	ft_memcpy(a, b, d);
	printf("%s\n", a);
} */
