/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_operations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dserra-d <dserra-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 15:18:24 by dserra-d          #+#    #+#             */
/*   Updated: 2026/05/28 09:39:49 by dserra-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	ra(t_stack *a, t_flags *flag)
{
	if (!a)
		return ;
	rotate (a);
	if (flag)
		flag->ra++;
	write (1, "ra\n", 3);
}

void	rb(t_stack *b, t_flags *flag)
{
	if (!b)
		return ;
	rotate (b);
	if (flag)
		flag->rb++;
	write (1, "rb\n", 3);
}

void	rr(t_stack *a, t_stack *b, t_flags *flag)
{
	if (!a || !b)
		return ;
	rotate (a);
	rotate (b);
	if (flag)
		flag->rr++;
	write (1, "rr\n", 3);
}
