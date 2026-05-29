/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dserra-d <dserra-d@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 12:48:10 by dserra-d          #+#    #+#             */
/*   Updated: 2026/05/26 13:59:35 by dserra-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

int	biggest_index(t_stack *b)
{
	int		biggest_index;
	int		position;
	int		cur_position;
	t_node	*i;

	biggest_index = INT_MIN;
	position = 0;
	cur_position = 0;
	i = b->top;
	while (i)
	{
		if (i->index > biggest_index)
		{
			biggest_index = i->index;
			position = cur_position;
		}
		cur_position++;
		i = i->next;
	}
	return (position);
}

void	move_index_top(t_stack *b, t_flags *flags)
{
	int	i;
	int	top;

	if (!b)
		return ;
	i = 0;
	top = biggest_index(b);
	if (top <= b->size / 2)
	{
		while (i < top)
		{
			rb (b, flags);
			i++;
		}
	}
	else
	{
		while (i < b->size - top)
		{
			rrb (b, flags);
			i++;
		}
	}
}

int	chuck_position(t_stack *a, int min, int max)
{
	int		position;
	t_node	*node;

	position = 0;
	node = a->top;
	while (node)
	{
		if (node->index >= min && node->index < max)
			return (position);
		position++;
		node = node->next;
	}
	return (-1);
}
