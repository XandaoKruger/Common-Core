/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acano-kr <acano-kr@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 14:40:34 by acano-kr          #+#    #+#             */
/*   Updated: 2026/05/14 11:54:13 by acano-kr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_words(const char *s, char c)
{
	size_t	i;
	size_t	words;

	i = 0;
	words = 0;
	while (s[i])
	{
		if (s[i] != c && (i == 0 || s[i - 1] == c))
			words++;
		i++;
	}
	return (words);
}

static char	**free_malloc(char **array)
{
	size_t	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
	return (NULL);
}

static char	**fill_array(char **res, const char *s, char c)
{
	size_t	i;
	size_t	wordi;
	size_t	start;

	i = 0;
	wordi = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		start = i;
		if (!s[i])
			break ;
		while (s[i] != c && s[i])
			i++;
		res[wordi] = ft_substr(s, start, i - start);
		if (!res[wordi])
			return (free_malloc(res));
		wordi++;
	}
	res[wordi] = NULL;
	return (res);
}

char	**ft_split(char const *s, char c)
{
	char	**result;

	if (!s)
		return (NULL);
	result = malloc(sizeof(char *) * (count_words(s, c) + 1));
	if (!result)
		return (NULL);
	result = fill_array(result, s, c);
	return (result);
}
/* 
#include <stdio.h>

int	main(void)
{
	int i = 0;
	char **str;
	
	str = ft_split("Takeo Mazaki Edward Richtofen Tank Dempsey",' ');
	while (str[i])
	{
		printf("%s\n", str[i]);
		i++;
	}
} */
