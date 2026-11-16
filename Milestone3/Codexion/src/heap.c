/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acano-kr <acano-kr@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/07 11:53:41 by acano-kr          #+#    #+#             */
/*   Updated: 2026/11/16 23:36:53 by acano-kr         ###   ########.fr       */
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