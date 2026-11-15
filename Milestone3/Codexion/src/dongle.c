/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acano-kr <acano-kr@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/07 11:53:36 by acano-kr          #+#    #+#             */
/*   Updated: 2026/11/15 16:09:06 by acano-kr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	take_dongle(t_dongle *d)
{
	pthread_mutex_lock(&d->lock);
	while (d->is_taken)
		pthread_cond_wait(&d->cond, &d->lock);
	d->is_taken = 1;
	pthread_mutex_unlock(&d->lock);
}

void	release_dongle(t_dongle *d)
{
	pthread_mutex_lock(&d->lock);
	d->is_taken = 0;
	pthread_cond_broadcast(&d->cond);
	pthread_mutex_unlock(&d->lock);
}

void	take_both(t_coder *coder)
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
	take_dongle(first);
	print_log(coder, "has taken a dongle");
	take_dongle(second);
	print_log(coder, "has taken a dongle");
}
