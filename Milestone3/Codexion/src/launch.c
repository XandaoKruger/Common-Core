/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acano-kr <acano-kr@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/21 21:58:09 by acano-kr          #+#    #+#             */
/*   Updated: 2026/11/21 22:02:05 by acano-kr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static void	join_all(t_sim *sim)
{
	int	i;

	i = 0;
	while (i < sim->config.coders)
	{
		pthread_join(sim->coders[i].thread, NULL);
		i++;
	}
	pthread_join(sim->monitor, NULL);
}

static void	abort_launch(t_sim *sim, int created)
{
	int	i;

	stop_sim(sim);
	i = 0;
	while (i < created)
	{
		pthread_join(sim->coders[i].thread, NULL);
		i++;
	}
}

int	launch_coders(t_sim *sim)
{
	int	i;

	sim->start_time = get_time_ms();
	i = 0;
	while (i < sim->config.coders)
	{
		sim->coders[i].last_compile_start = sim->start_time;
		if (pthread_create(&sim->coders[i].thread, NULL,
				coder_routine, &sim->coders[i]))
		{
			abort_launch(sim, i);
			return (0);
		}
		i++;
	}
	if (pthread_create(&sim->monitor, NULL, monitor_routine, sim))
	{
		abort_launch(sim, i);
		return (0);
	}
	join_all(sim);
	return (1);
}
