/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acano-kr <acano-kr@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 15:11:02 by acano-kr          #+#    #+#             */
/*   Updated: 2026/04/19 15:11:02 by acano-kr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	j;
	size_t	len;
	char	*str;

	len = ft_strlen(s1);
	i = 0;
	j = len - 1;
	while (ft_strchr(set, s1[i]))
		i++;
	while (ft_strchr(set, s1[j]))
		j--;
	str = ft_substr(s1, i, j - i + 1);
	return (str);
}

/* #include <stdio.h>

int	main(void)
{
	char	a[] = "ZxxEuronymousxxZ";
	char	set[] = "Zxx";
	char	*str = ft_strtrim(a, set);

	printf("%s\n", str);
} */
