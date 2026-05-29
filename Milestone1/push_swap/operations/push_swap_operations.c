/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_operations.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dserra-d <dserra-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 14:02:39 by dserra-d          #+#    #+#             */
/*   Updated: 2026/05/28 09:39:17 by dserra-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	sa(t_stack *a, t_flags *flag)
{
	if (!a)
		return ;
	swap (a);
	if (flag)
		flag->sa++;
	write (1, "sa\n", 3);
}

void	sb(t_stack *b, t_flags *flag)
{
	if (!b)
		return ;
	swap (b);
	if (flag)
		flag->sb++;
	write (1, "sb\n", 3);
}

void	ss(t_stack *a, t_stack *b, t_flags *flag)
{
	if (!a || !b)
		return ;
	swap (a);
	swap (b);
	if (flag)
		flag->ss++;
	write (1, "ss\n", 3);
}

void	pa(t_stack *a, t_stack *b, t_flags *flag)
{
	t_node	*first_b;
	t_node	*first_a;

	if (!a || !b || b->size == 0)
		return ;
	first_b = b->top;
	first_a = a->top;
	b->top = first_b->next;
	first_b->next = first_a;
	first_b->prev = NULL;
	a->top = first_b;
	a->size++;
	b->size--;
	if (first_a)
		first_a->prev = first_b;
	if (b->top)
		b->top->prev = NULL;
	if (b->size == 0)
		b->bottom = NULL;
	if (a->size == 1)
		a->bottom = first_b;
	if (flag)
		flag->pa++;
	write (1, "pa\n", 3);
}

void	pb(t_stack *a, t_stack *b, t_flags *flag)
{
	t_node	*first_a;
	t_node	*first_b;

	if (!a || !b || a->size == 0)
		return ;
	first_a = a->top;
	first_b = b->top;
	a->top = first_a->next;
	first_a->next = first_b;
	first_a->prev = NULL;
	b->top = first_a;
	b->size++;
	a->size--;
	if (first_b)
		first_b->prev = first_a;
	if (a->top)
		a->top->prev = NULL;
	if (a->size == 0)
		a->bottom = NULL;
	if (b->size == 1)
		b->bottom = first_a;
	if (flag)
		flag->pb++;
	write (1, "pb\n", 3);
}
