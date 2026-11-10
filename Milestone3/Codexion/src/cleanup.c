/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acano-kr <acano-kr@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/07 11:53:32 by acano-kr          #+#    #+#             */
/*   Updated: 2026/11/10 10:28:18 by acano-kr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	cleanup_sim(t_sim *sim)
{
	int	i;

	i = 0;
	while (sim->dongles && i < sim->config.coders)
	{
		pthread_mutex_destroy(&sim->dongles[i].lock);
		pthread_cond_destroy(&sim->dongles[i].cond);
		free(sim->dongles[i].queue.data);
		i++;
	}
	i = 0;
	while (sim->coders && i < sim->config.coders)
	{
		pthread_mutex_destroy(&sim->coders[i].lock);
		i++;
	}
	pthread_mutex_destroy(&sim->log_lock);
	free(sim->dongles);
	free(sim->coders);
}
