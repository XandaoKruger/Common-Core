/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_simple.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dserra-d <dserra-d@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/22 11:15:17 by dserra-d          #+#    #+#             */
/*   Updated: 2026/05/26 13:57:45 by dserra-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	sort_two(t_stack *a, t_flags *flags)
{
	if (!a)
		return ;
	if (a->top->value > a->top->next->value)
		sa(a, flags);
}

void	sort_three(t_stack *a, t_flags *flags)
{
	t_node	*x;
	t_node	*y;
	t_node	*z;

	if (!a)
		return ;
	x = a->top;
	y = a->top->next;
	z = a->bottom;
	if (y->value < x->value && y->value < z->value && x->value < z->value)
		sa (a, flags);
	else if (x->value < y->value && y->value > z->value && x->value > z->value)
		rra (a, flags);
	else if (x->value > y->value && y->value < z->value && x->value > z->value)
		ra (a, flags);
	else if (x->value < y->value && y->value > z->value && x->value < z->value)
	{
		rra (a, flags);
		sa (a, flags);
	}
	else if (x->value > y->value && y->value > z->value && x->value > z->value)
	{
		sa (a, flags);
		rra (a, flags);
	}
}

void	sort_simple(t_stack *a, t_stack *b, t_flags *flags)
{
	if (!a || !b)
		return ;
	if (a->size == 2)
		sort_two (a, flags);
	else if (a->size == 3)
		sort_three (a, flags);
	else
	{
		while (a->size > 0)
		{
			move_smallest_top(a, flags);
			pb(a, b, flags);
		}
		while (b->size > 0)
		{
			pa(a, b, flags);
		}
	}
}
