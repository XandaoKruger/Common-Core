/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_operations.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dserra-d <dserra-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 15:27:31 by dserra-d          #+#    #+#             */
/*   Updated: 2026/05/28 09:39:34 by dserra-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	rra(t_stack *a, t_flags *flag)
{
	if (!a)
		return ;
	reverse (a);
	if (flag)
		flag->rra++;
	write (1, "rra\n", 4);
}

void	rrb(t_stack *b, t_flags *flag)
{
	if (!b)
		return ;
	reverse (b);
	if (flag)
		flag->rrb++;
	write (1, "rrb\n", 4);
}

void	rrr(t_stack *a, t_stack *b, t_flags *flag)
{
	if (!a || !b)
		return ;
	reverse (a);
	reverse (b);
	if (flag)
		flag->rrr++;
	write (1, "rrr\n", 4);
}
