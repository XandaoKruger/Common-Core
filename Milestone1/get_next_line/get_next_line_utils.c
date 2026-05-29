/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acano-kr <acano-kr@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 16:03:56 by acano-kr          #+#    #+#             */
/*   Updated: 2026/05/12 09:22:01 by acano-kr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	len;
	size_t	i;
	size_t	lens1;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen((char *)s1) + ft_strlen((char *)s2) + 1;
	lens1 = ft_strlen((char *)s1);
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

char	*ft_strchr(char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i++;
	}
	if (!(char)c)
		return ((char *)&s[i]);
	return (0);
}

char	*ft_strdup(const char *s1)
{
	char	*str;
	size_t	len;
	size_t	i;

	if (!s1)
		return (NULL);
	len = ft_strlen((char *)s1) + 1;
	str = malloc(sizeof(char) * len);
	if (!str)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	a;
	size_t	i;

	if (!s)
		return (NULL);
	a = ft_strlen((char *)s);
	if (start >= a)
		return (ft_strdup(""));
	if (len > a - start)
		len = a - start;
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (i < len)
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
