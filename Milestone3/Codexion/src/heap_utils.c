/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acano-kr <acano-kr@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/07 11:53:39 by acano-kr          #+#    #+#             */
/*   Updated: 2026/11/17 12:26:13 by acano-kr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	req_less(t_req a, t_req b)
{
	if (a.key != b.key)
		return (a.key < b.key);
	return (a.coder_id < b.coder_id);
}

void	req_swap(t_req *a, t_req *b)
{
	t_req	temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

void	shift_up(t_heap *h, int i)
{
	int	parent;

	while (i > 0)
	{
		parent = (i - 1) / 2;
		if (!req_less(h->data[i], h->data[parent]))
			return ;
		req_swap(&h->data[i], &h->data[parent]);
		i = parent;
	}
}

void	shift_down(t_heap *h, int i)
{
	int	son;

	while (2 * i + 1 < h->size)
	{
		son = 2 * i + 1;
		if (son + 1 < h->size && req_less(h->data[son + 1], h->data[son]))
			son++;
		if (!req_less(h->data[son], h->data[i]))
			return ;
		req_swap(&h->data[i], &h->data[son]);
		i = son;
	}
}
