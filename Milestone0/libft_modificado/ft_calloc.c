/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acano-kr <acano-kr@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 17:23:55 by acano-kr          #+#    #+#             */
/*   Updated: 2026/04/16 17:23:55 by acano-kr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*str;

	if (size && count > SIZE_MAX / size)
		return (NULL);
	str = malloc(count * size);
	if (str == NULL)
		return (NULL);
	ft_bzero(str, count * size);
	return (str);
}

/*#include <stdio.h>

int	main(void)
{
	size_t a = 10;
	size_t b = 4;
	char *str = ft_calloc(a, b);

	printf("%s\n", str);
	free(str);
	return (0);
} */
