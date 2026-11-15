/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acano-kr <acano-kr@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/07 11:53:36 by acano-kr          #+#    #+#             */
/*   Updated: 2026/11/15 17:51:37 by acano-kr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	take_dongle(t_dongle *d, t_sim *sim)
{
	pthread_mutex_lock(&d->lock);
	while (d->is_taken && !is_stopped(sim))
		pthread_cond_wait(&d->cond, &d->lock);
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

void	release_dongle(t_dongle *d)
{
	pthread_mutex_lock(&d->lock);
	d->is_taken = 0;
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
		release_dongle(first);
		return (0);
	}
	print_log(coder, "has taken a dongle");
	return (1);
}
