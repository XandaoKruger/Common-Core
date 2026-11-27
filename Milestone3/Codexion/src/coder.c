/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acano-kr <acano-kr@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/07 11:53:34 by acano-kr          #+#    #+#             */
/*   Updated: 2026/11/27 23:04:08 by acano-kr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static void	do_phase(t_coder *coder, const char *msg, long ms)
{
	print_log(coder, msg);
	ms_sleep(ms, coder->sim);
}

static void	do_compile(t_coder *coder)
{
	pthread_mutex_lock(&coder->lock);
	coder->last_compile_start = get_time_ms();
	pthread_mutex_unlock(&coder->lock);
	do_phase(coder, "is compiling", coder->sim->config.compile);
	pthread_mutex_lock(&coder->lock);
	coder->compile_count++;
	pthread_mutex_unlock(&coder->lock);
}

void	*coder_routine(void *arg)
{
	t_coder	*coder;
	int		i;

	coder = (t_coder *)arg;
	i = 0;
	while (i < coder->sim->config.compiles_required && !is_stopped(coder->sim))
	{
		if (!take_both(coder))
			break ;
		do_compile(coder);
		release_both(coder);
		do_phase(coder, "is debugging", coder->sim->config.debug);
		do_phase(coder, "is refactoring", coder->sim->config.refactor);
		i++;
	}
	return (NULL);
}

int	is_urgent(t_coder *c, long now)
{
	long	last;

	pthread_mutex_lock(&c->lock);
	last = c->last_compile_start;
	pthread_mutex_unlock(&c->lock);
	return (now - last >= c->sim->config.burnout / 2);
}
