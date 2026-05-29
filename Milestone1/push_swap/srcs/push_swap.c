/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acano-kr <acano-kr@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 12:00:05 by acano-kr          #+#    #+#             */
/*   Updated: 2026/05/27 08:00:19 by acano-kr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	error(void)
{
	ft_putstr_fd("Error\n", 2);
	exit(1);
}

static int	ft_count_args(int argc, char **argv, int start_i)
{
	int		total;
	int		i;
	int		j;
	char	**split;

	total = 0;
	i = start_i;
	while (i < argc)
	{
		split = ft_split(argv[i], ' ');
		j = 0;
		while (split[j])
		{
			total++;
			j++;
		}
		j = 0;
		while (split[j])
			free(split[j++]);
		free(split);
		i++;
	}
	return (total);
}

static char	**ft_get_args(int argc, char **argv, int *size, int start_i)
{
	int		i;
	int		j;
	int		k;
	char	**final_array;
	char	**split;

	*size = ft_count_args(argc, argv, start_i);
	final_array = malloc(sizeof(char **) * (*size + 1));
	if (!final_array)
		return (NULL);
	k = 0;
	i = start_i;
	while (i < argc)
	{
		split = ft_split(argv[i], ' ');
		j = 0;
		while (split[j])
			final_array[k++] = split[j++];
		free(split);
		i++;
	}
	final_array[k] = NULL;
	return (final_array);
}

char	**init_program(int argc, char **argv, t_flags *flags, int *size)
{
	int		start_i;
	char	**args;

	start_i = get_flag(argc, argv, flags);
	if (start_i == -1)
		return (*size = -1, error(), NULL);
	if (start_i == argc)
		return (*size = 0, NULL);
	args = ft_get_args(argc, argv, size, start_i);
	if (!args)
		return (error(), NULL);
	return (args);
}

int	setup_stacks(char **args, t_stack **a, t_stack **b, int size)
{
	int		*values;

	values = parse_args(args, size, &size);
	if (!values)
		return (0);
	*a = ft_init_stack(values, size);
	if (!*a)
		return (free(values), 0);
	*b = ft_init_empty();
	if (!*b)
		return (free(values), ft_free_stack(*a), 0);
	free(values);
	return (1);
}
