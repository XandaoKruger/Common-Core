/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acano-kr <acano-kr@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 13:29:51 by acano-kr          #+#    #+#             */
/*   Updated: 2026/05/25 10:20:03 by acano-kr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

static int	ft_valid_int(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static int	ft_duplicate(int *array, int size, int value)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (array[i] == value)
			return (1);
		i++;
	}
	return (0);
}

int	*parse_args(char **args, int count, int *size)
{
	int		*array;
	long	val;
	int		i;

	array = malloc(sizeof(int) * count);
	if (!array)
		return (NULL);
	i = 0;
	while (i < count)
	{
		if (!ft_valid_int(args[i]))
			return (free(array), NULL);
		val = ft_atol(args[i]);
		if (val > INT_MAX || val < INT_MIN)
			return (free(array), NULL);
		if (ft_duplicate(array, i, (int)val))
			return (free(array), NULL);
		array[i] = (int)val;
		i++;
	}
	*size = count;
	return (array);
}
