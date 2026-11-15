/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acano-kr <acano-kr@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/07 11:53:50 by acano-kr          #+#    #+#             */
/*   Updated: 2026/11/15 22:54:54 by acano-kr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	is_burned_out(t_coder *coder)
{
	long	last;
	int		count;

	pthread_mutex_lock(&coder->lock);
	last = coder->last_compile_start;
	count = coder->compile_count;
	pthread_mutex_unlock(&coder->lock);
	if (count >= coder->sim->config.compiles_required)
		return (0);
	return (get_time_ms() - last >= coder->sim->config.burnout);
}

void	declare_burnout(t_coder *coder)
{
	t_sim	*sim;

	sim = coder->sim;
	pthread_mutex_lock(&sim->log_lock);
	if (!sim->stop)
	{
		sim->stop = 1;
		printf("%ld %d %s\n",
			get_time_ms() - sim->start_time, coder->id, "burned out");
	}
	pthread_mutex_unlock(&sim->log_lock);
}

int	check_burnout(t_sim *sim)
{
	int	i;

	i = 0;
	while (i < sim->config.coders)
	{
		if (is_burned_out(&sim->coders[i]))
		{
			declare_burnout(&sim->coders[i]);
			wake_dongles(sim);
			return (1);
		}
		i++;
	}
	return (0);
}

void	*monitor_routine(void *arg)
{
	t_sim	*sim;

	sim = (t_sim *)arg;
	while (1)
	{
		if (check_burnout(sim))
			return (NULL);
		if (all_done(sim))
		{
			stop_sim(sim);
			return (NULL);
		}
		usleep(1000);
	}
}
