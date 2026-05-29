/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acano-kr <acano-kr@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 17:40:07 by acano-kr          #+#    #+#             */
/*   Updated: 2026/05/26 08:09:00 by acano-kr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

long long	ft_atol(const char *str)
{
	long long	i;
	long long	res;
	long long	sin;

	i = 0;
	sin = 1;
	res = 0;
	while ((str[i] == 32) || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sin = -sin;
		i++;
	}
	while ((ft_isdigit(str[i])) && str[i])
	{
		res = res * 10 + (str[i] - '0');
		i++;
	}
	return (res * sin);
}

void	ft_free_args(char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
}

int	is_sorted(t_stack *stack)
{
	t_node	*current;

	if (!stack || stack->size <= 1)
		return (1);
	current = stack->top;
	while (current->next)
	{
		if (current->value > current->next->value)
			return (0);
		current = current->next;
	}
	return (1);
}
