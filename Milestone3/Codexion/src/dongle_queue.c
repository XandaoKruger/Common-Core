/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongle_queue.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acano-kr <acano-kr@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/17 13:41:38 by acano-kr          #+#    #+#             */
/*   Updated: 2026/11/24 16:17:08 by acano-kr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static int	dongle_ready(t_dongle *d, long now)
{
	return (!d->is_taken && now >= d->available_at);
}

static int	may_take(t_dongle *d, t_coder *c, long now)
{
	t_req	top;
	t_coder	*other;

	if (!heap_peek(&d->queue, &top))
		return (0);
	if (top.coder_id == c->id)
		return (1);
	other = &c->sim->coders[top.coder_id - 1];
	return (!(dongle_ready(other->left, now)
			&& dongle_ready(other->right, now)));
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

int	enqueue_both(t_coder *coder)
{
	if (!queue_request(coder->left, coder))
		return (0);
	if (coder->right == coder->left)
		return (1);
	return (queue_request(coder->right, coder));
}

int	can_go(t_coder *coder, long now)
{
	if (coder->left == coder->right)
		return (0);
	return (dongle_ready(coder->left, now)
		&& dongle_ready(coder->right, now)
		&& may_take(coder->left, coder, now)
		&& may_take(coder->right, coder, now));
}
