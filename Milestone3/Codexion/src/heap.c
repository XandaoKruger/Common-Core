/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acano-kr <acano-kr@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/07 11:53:41 by acano-kr          #+#    #+#             */
/*   Updated: 2026/11/17 12:40:12 by acano-kr         ###   ########.fr       */
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
