/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongle_queue.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acano-kr <acano-kr@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/17 13:41:38 by acano-kr          #+#    #+#             */
/*   Updated: 2026/11/17 13:54:29 by acano-kr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	is_my_turn(t_dongle *d, int id)
{
	t_req	top;

	if (!heap_peek(&d->queue, &top))
		return (0);
	return (top.coder_id == id);
}

int	queue_request(t_dongle *d, t_coder *coder)
{
	t_req	r;

	r.coder_id = coder->id;
	if (coder->sim->config.sched == FIFO)
		r.key = d->arrivals++;
	else
	{
		pthread_mutex_lock(&coder->lock);
		r.key = coder->last_compile_start + coder->sim->config.burnout;
		pthread_mutex_unlock(&coder->lock);
	}
	return (heap_push(&d->queue, r));
}
