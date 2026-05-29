/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acano-kr <acano-kr@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 02:03:55 by acano-kr          #+#    #+#             */
/*   Updated: 2026/04/19 02:03:55 by acano-kr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	len;
	size_t	i;
	size_t	lens1;

	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	lens1 = ft_strlen(s1);
	str = malloc(sizeof(char) * len);
	if (!str)
		return (NULL);
	i = 0;
	while (i < len)
	{
		if (i < lens1)
			str[i] = s1[i];
		if (i >= lens1)
			str[i] = s2[i - lens1];
		i++;
	}
	str[len - 1] = '\0';
	return (str);
}

/* #include <stdio.h>

int	main(void)
{
	char a[] = "Edward";
	char b[] = "Richtofen";
	char *str = ft_strjoin(a, b);

	printf("%s\n", str);
	free(str);
} */
