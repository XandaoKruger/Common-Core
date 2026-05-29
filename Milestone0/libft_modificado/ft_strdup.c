/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acano-kr <acano-kr@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 18:07:17 by acano-kr          #+#    #+#             */
/*   Updated: 2026/04/16 18:07:17 by acano-kr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*str;
	size_t	len;

	len = ft_strlen(s1) + 1;
	str = malloc(sizeof(char) * len);
	if (!str)
		return (NULL);
	ft_memcpy(str, s1, len);
	return (str);
}

/* #include <stdio.h>

int	main(void)
{
	char a[] = "Nuketown";
	char *dup = ft_strdup(a);

	printf("%s\n", dup);
} */
