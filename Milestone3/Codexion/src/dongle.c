/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acano-kr <acano-kr@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/07 11:53:36 by acano-kr          #+#    #+#             */
/*   Updated: 2026/11/16 13:17:31 by acano-kr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static void	wait_dongle(t_dongle *d)
{
	struct timespec ts;

	if (d->is_taken)
		pthread_cond_wait(&d->cond, &d->lock);
	else
	{
		ts.tv_sec = d->available_at / 1000;
		ts.tv_nsec = (d->available_at % 1000) / 1000000;
		pthread_cond_timedwait(&d->cond, &d->lock, &ts);
	}
}

int	take_dongle(t_dongle *d, t_sim *sim)
{
	pthread_mutex_lock(&d->lock);
	while (!is_stopped(sim) && (d->is_taken || get_time_ms() < d->available_at))
		wait_dongle(d);
	if (is_stopped(sim))
	{
		pthread_mutex_unlock(&d->lock);
		return (0);
	}
	else
	{
		d->is_taken = 1;
		pthread_mutex_unlock(&d->lock);
		return (1);
	}
}

void	release_dongle(t_dongle *d, long cooldown)
{
	pthread_mutex_lock(&d->lock);
	d->is_taken = 0;
	d->available_at = get_time_ms() + cooldown;
	pthread_cond_broadcast(&d->cond);
	pthread_mutex_unlock(&d->lock);
}

int	take_both(t_coder *coder)
{
	t_dongle	*first;
	t_dongle	*second;

	if (coder->left < coder->right)
	{
		first = coder->left;
		second = coder->right;
	}
	else
	{
		first = coder->right;
		second = coder->left;
	}
	if (!take_dongle(first, coder->sim))
		return (0);
	print_log(coder, "has taken a dongle");
	if (!take_dongle(second, coder->sim))
	{
		release_dongle(first, coder->sim->config.cooldown);
		return (0);
	}
	print_log(coder, "has taken a dongle");
	return (1);
}
