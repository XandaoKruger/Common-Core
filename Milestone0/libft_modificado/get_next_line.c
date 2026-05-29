/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acano-kr <acano-kr@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 12:12:28 by acano-kr          #+#    #+#             */
/*   Updated: 2026/05/19 01:29:52 by acano-kr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*read_until(int fd, char *buffer, char *remi)
{
	int		rbyt;
	char	*temp;

	if (!remi)
		remi = ft_strdup("");
	if (!remi)
		return (NULL);
	rbyt = 1;
	while (rbyt > 0 && !ft_strchr(remi, '\n'))
	{
		rbyt = read(fd, buffer, BUFFER_SIZE);
		if (rbyt == -1 || (rbyt == 0 && *remi == '\0'))
		{
			free(remi);
			return (NULL);
		}
		buffer[rbyt] = '\0';
		temp = remi;
		remi = ft_strjoin(remi, buffer);
		free(temp);
		if (!remi)
			return (NULL);
	}
	return (remi);
}

char	*extr_line(char *remind)
{
	int	i;

	if (!remind || *remind == '\0')
		return (NULL);
	i = 0;
	while (remind[i] && remind[i] != '\n')
		i++;
	if (remind[i] == '\n')
		i++;
	return (ft_substr(remind, 0, i));
}

char	*updt_reminder(char *remin)
{
	char	*novo;
	int		a;

	if (!remin)
		return (NULL);
	if (*remin == '\0')
	{
		free(remin);
		return (NULL);
	}
	a = 0;
	while (remin[a] && remin[a] != '\n')
		a++;
	if (!remin[a])
	{
		free(remin);
		return (NULL);
	}
	novo = ft_strdup(remin + a + 1);
	free(remin);
	if (!novo || *novo == '\0')
		return (free(novo), NULL);
	return (novo);
}

char	*get_next_line(int fd)
{
	static char	*reminder;
	char		*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (free(reminder), reminder = NULL, NULL);
	reminder = read_until(fd, buffer, reminder);
	free(buffer);
	if (!reminder || *reminder == '\0')
	{
		if (reminder)
			free(reminder);
		reminder = NULL;
		return (NULL);
	}
	line = extr_line(reminder);
	if (!line)
		return (free(reminder), reminder = NULL, NULL);
	reminder = updt_reminder(reminder);
	return (line);
}
