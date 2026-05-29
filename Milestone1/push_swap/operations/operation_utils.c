/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acano-kr <acano-kr@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/23 10:10:15 by dserra-d          #+#    #+#             */
/*   Updated: 2026/05/25 10:19:38 by acano-kr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	swap(t_stack *s)
{
	t_node	*first;
	t_node	*second;
	t_node	*third;

	if (!s || s->size <= 1)
		return ;
	first = s->top;
	second = s->top->next;
	third = second->next;
	s->top = second;
	second->prev = NULL;
	second->next = first;
	first->prev = second;
	first->next = third;
	if (third)
		third->prev = first;
}

void	reverse(t_stack *s)
{
	t_node	*old_top;
	t_node	*old_bottom;
	t_node	*new_bottom;

	if (!s || s->size <= 1)
		return ;
	old_bottom = s->bottom;
	new_bottom = old_bottom->prev;
	old_top = s->top;
	s->top = old_bottom;
	s->bottom = new_bottom;
	old_bottom->prev = NULL;
	old_top->prev = old_bottom;
	new_bottom->next = NULL;
	old_bottom->next = old_top;
}

void	rotate(t_stack *s)
{
	t_node	*old_top;
	t_node	*old_bottom;

	if (!s || s->size <= 1)
		return ;
	old_top = s->top;
	s->top = old_top->next;
	old_bottom = s->bottom;
	old_top->prev = old_bottom;
	old_top->next = NULL;
	old_bottom->next = old_top;
	s->top->prev = NULL;
	s->bottom = old_top;
}
