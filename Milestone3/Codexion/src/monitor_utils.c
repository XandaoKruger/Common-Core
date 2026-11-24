/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acano-kr <acano-kr@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/15 22:25:27 by acano-kr          #+#    #+#             */
/*   Updated: 2026/11/24 12:34:18 by acano-kr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	wake_dongles(t_sim *sim)
{
	pthread_mutex_lock(&sim->table_lock);
	pthread_cond_broadcast(&sim->table_cond);
	pthread_mutex_unlock(&sim->table_lock);
}

int	all_done(t_sim *sim)
{
	int	i;
	int	count;

	i = 0;
	while (i < sim->config.coders)
	{
		pthread_mutex_lock(&sim->coders[i].lock);
		count = sim->coders[i].compile_count;
		pthread_mutex_unlock(&sim->coders[i].lock);
		if (count < sim->config.compiles_required)
			return (0);
		i++;
	}
	return (1);
}

void	stop_sim(t_sim *sim)
{
	pthread_mutex_lock(&sim->log_lock);
	sim->stop = 1;
	pthread_mutex_unlock(&sim->log_lock);
	wake_dongles(sim);
}
