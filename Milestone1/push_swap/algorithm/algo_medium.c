/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_medium.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dserra-d <dserra-d@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 11:00:50 by dserra-d          #+#    #+#             */
/*   Updated: 2026/05/26 14:34:49 by dserra-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

static	void	pass_to_b(t_stack *a, t_stack *b, t_chunk chunk, t_flags *flags)
{
	int	i;
	int	position;
	int	min;
	int	max;

	i = a->size;
	min = chunk.min;
	max = chunk.max;
	while (i > 0)
	{
		if (a->top->index >= min && a->top->index < max)
			pb(a, b, flags);
		else
		{
			position = chuck_position(a, min, max);
			if (position <= a->size / 2)
				ra (a, flags);
			else
				rra (a, flags);
		}
		i--;
	}
}

void	sort_medium(t_stack *a, t_stack *b, t_flags *flags)
{
	int		chunk;
	int		chunk_size;
	int		total_chunks;
	t_chunk	c;

	if (!a || !b)
		return ;
	set_index(a);
	chunk_size = ft_sqrt(a->size) + ft_sqrt(a->size) / 2;
	total_chunks = a->size / chunk_size + 1;
	chunk = 0;
	while (chunk < total_chunks)
	{
		c.min = chunk * chunk_size;
		c.max = (chunk + 1) * chunk_size;
		pass_to_b(a, b, c, flags);
		chunk++;
	}
	while (b->size > 0)
	{
		move_index_top(b, flags);
		pa (a, b, flags);
	}
}
