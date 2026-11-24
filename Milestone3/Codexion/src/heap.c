/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acano-kr <acano-kr@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/07 11:53:41 by acano-kr          #+#    #+#             */
/*   Updated: 2026/11/24 12:50:12 by acano-kr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	heap_push(t_heap *h, t_req r)
{
	if (h->size == h->capacity)
		return (0);
	h->data[h->size] = r;
	h->size++;
	shift_up(h, h->size - 1);
	return (1);
}

int	heap_peek(t_heap *h, t_req *out)
{
	if (h->size == 0)
		return (0);
	*out = h->data[0];
	return (1);
}

int	heap_pop(t_heap *h, t_req *out)
{
	if (h->size == 0)
		return (0);
	*out = h->data[0];
	h->size--;
	h->data[0] = h->data[h->size];
	shift_down(h, 0);
	return (1);
}

void	heap_remove(t_heap *h, int id)
{
	int	i;

	i = 0;
	while (i < h->size && h->data[i].coder_id != id)
		i++;
	if (i == h->size)
		return ;
	h->size--;
	h->data[i] = h->data[h->size];
	if (i < h->size)
	{
		shift_down(h, i);
		shift_up(h, i);
	}
}
