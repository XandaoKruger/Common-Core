/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acano-kr <acano-kr@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/07 11:53:34 by acano-kr          #+#    #+#             */
/*   Updated: 2026/11/15 16:52:42 by acano-kr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static void	do_phase(t_coder *coder, const char *msg, long ms)
{
	print_log(coder, msg);
	ms_sleep(ms);
}

void	*coder_routine(void *arg)
{
	t_coder	*coder;
	int		i;

	coder = (t_coder *)arg;
	i = 0;
	while (i < coder->sim->config.compiles_required)
	{
		take_both(coder);
		pthread_mutex_lock(&coder->lock);
		coder->last_compile_start = get_time_ms();
		pthread_mutex_unlock(&coder->lock);
		do_phase(coder, "is compiling", coder->sim->config.compile);
		pthread_mutex_lock(&coder->lock);
		coder->compile_count++;
		pthread_mutex_unlock(&coder->lock);
		release_dongle(coder->left);
		release_dongle(coder->right);
		do_phase(coder, "is debugging", coder->sim->config.debug);
		do_phase(coder, "is refactoring", coder->sim->config.refactor);
		i++;
	}
	return (NULL);
}

int	launch_coders(t_sim *sim)
{
	int	i;

	sim->start_time = get_time_ms();
	i = 0;
	while (i < sim->config.coders)
	{
		sim->coders[i].last_compile_start = sim->start_time;
		if (pthread_create(&sim->coders[i].thread, NULL, coder_routine,
				&sim->coders[i]))
			return (0);
		i++;
	}
	i = 0;
	while (i < sim->config.coders)
	{
		pthread_join(sim->coders[i].thread, NULL);
		i++;
	}
	return (1);
}
