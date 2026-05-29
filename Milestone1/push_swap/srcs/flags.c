/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dserra-d <dserra-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/25 11:25:04 by acano-kr          #+#    #+#             */
/*   Updated: 2026/05/28 09:38:48 by dserra-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

static int	is_flag(char *input, char *expected)
{
	int	in;
	int	ex;

	in = ft_strlen(input);
	ex = ft_strlen(expected);
	if (in == ex)
	{
		if (ft_strncmp(input, expected, ex) == 0)
			return (1);
	}
	return (0);
}

int	get_flag(int argc, char **argv, t_flags *flags)
{
	int	i;

	ft_bzero(flags, sizeof(t_flags));
	i = 1;
	while (i < argc && ft_strncmp(argv[i], "--", 2) == 0)
	{
		if (is_flag(argv[i] + 2, "bench"))
			flags->bench = 1;
		else if (is_flag(argv[i] + 2, "adaptive"))
			flags->strategy = FLAG_ADAPTIVE;
		else if (is_flag(argv[i] + 2, "simple"))
			flags->strategy = FLAG_SIMPLE;
		else if (is_flag(argv[i] + 2, "medium"))
			flags->strategy = FLAG_MEDIUM;
		else if (is_flag(argv[i] + 2, "complex"))
			flags->strategy = FLAG_COMPLEX;
		else
			return (-1);
		i++;
	}
	return (i);
}

static	void	adaptive_sort(t_stack *a, t_stack *b, t_flags *flags)
{
	if (a->size <= 5)
	{
		flags->used_strategy = FLAG_SIMPLE;
		sort_simple(a, b, flags);
		return ;
	}
	if (flags->disorder < 0.2f)
	{
		flags->used_strategy = FLAG_SIMPLE;
		sort_simple(a, b, flags);
	}
	else if (flags->disorder < 0.5f)
	{
		flags->used_strategy = FLAG_MEDIUM;
		sort_medium(a, b, flags);
	}
	else
	{
		flags->used_strategy = FLAG_COMPLEX;
		sort_complex(a, b, flags);
	}
}

void	execute_strat(t_stack *stack_a, t_stack *stack_b, t_flags *flags)
{
	if (is_sorted(stack_a))
		return ;
	flags->disorder = calculate_disorder(stack_a);
	if (flags->strategy == FLAG_SIMPLE)
	{
		flags->used_strategy = FLAG_SIMPLE;
		sort_simple(stack_a, stack_b, flags);
	}
	else if (flags->strategy == FLAG_MEDIUM)
	{
		flags->used_strategy = FLAG_MEDIUM;
		sort_medium(stack_a, stack_b, flags);
	}
	else if (flags->strategy == FLAG_COMPLEX)
	{
		flags->used_strategy = FLAG_COMPLEX;
		sort_complex(stack_a, stack_b, flags);
	}
	else if (flags->strategy == FLAG_ADAPTIVE)
		adaptive_sort(stack_a, stack_b, flags);
	if (flags->bench == 1)
		print_bench(flags);
}
