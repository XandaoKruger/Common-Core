/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acano-kr <acano-kr@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/07 11:53:43 by acano-kr          #+#    #+#             */
/*   Updated: 2026/11/10 10:28:15 by acano-kr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static int	init_dongles(t_sim *sim)
{
	int			i;
	t_dongle	*d;

	i = 0;
	while (i < sim->config.coders)
	{
		d = &sim->dongles[i];
		if (pthread_mutex_init(&d->lock, NULL)
			|| pthread_cond_init(&d->cond, NULL))
			return (0);
		d->queue.data = malloc(sizeof(t_req) * sim->config.coders);
		if (!d->queue.data)
			return (0);
		d->queue.capacity = sim->config.coders;
		i++;
	}
	return (1);
}

static int	init_coders(t_sim *sim)
{
	int			i;
	t_coder		*c;

	i = 0;
	while (i < sim->config.coders)
	{
		c = &sim->coders[i];
		c->id = i + 1;
		c->sim = sim;
		c->left = &sim->dongles[i];
		c->right = &sim->dongles[(i + 1) % sim->config.coders];
		if (pthread_mutex_init(&c->lock, NULL))
			return (0);
		i++;
	}
	return (1);
}

int	init_sim(t_sim *sim)
{
	long	n;

	n = sim->config.coders;
	sim->coders = malloc(sizeof(t_coder) * n);
	sim->dongles = malloc(sizeof(t_dongle) * n);
	if (!sim->coders || !sim->dongles)
		return (0);
	memset(sim->coders, 0, sizeof(t_coder) * n);
	memset(sim->dongles, 0, sizeof(t_dongle) * n);
	if (pthread_mutex_init(&sim->log_lock, NULL))
		return (0);
	return (init_dongles(sim) && init_coders(sim));
}
