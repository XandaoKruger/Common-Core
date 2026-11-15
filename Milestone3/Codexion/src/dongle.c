/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acano-kr <acano-kr@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/07 11:53:36 by acano-kr          #+#    #+#             */
/*   Updated: 2026/11/15 14:18:25 by acano-kr         ###   ########.fr       */
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
