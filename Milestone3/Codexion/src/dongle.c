/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acano-kr <acano-kr@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/07 11:53:36 by acano-kr          #+#    #+#             */
/*   Updated: 2026/11/24 22:31:26 by acano-kr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static void	wait_both(t_coder *c)
{
	t_sim			*sim;
	long			until;

	sim = c->sim;
	until = c->left->available_at;
	if (c->right->available_at > until)
		until = c->right->available_at;
	if (!c->left->is_taken && !c->right->is_taken
		&& get_time_ms() < until)
	{
		pthread_mutex_unlock(&sim->table_lock);
		usleep(500);
		pthread_mutex_lock(&sim->table_lock);
	}
	else
		pthread_cond_wait(&sim->table_cond, &sim->table_lock);
}

static void	claim_both(t_coder *c)
{
	heap_remove(&c->left->queue, c->id);
	heap_remove(&c->right->queue, c->id);
	c->left->is_taken = 1;
	c->right->is_taken = 1;
}

int	take_both(t_coder *c)
{
	t_sim	*sim;

	sim = c->sim;
	pthread_mutex_lock(&sim->table_lock);
	if (!enqueue_both(c))
	{
		pthread_mutex_unlock(&sim->table_lock);
		return (0);
	}
	while (!is_stopped(sim) && !can_go(c, get_time_ms()))
		wait_both(c);
	if (is_stopped(sim))
	{
		pthread_mutex_unlock(&sim->table_lock);
		return (0);
	}
	claim_both(c);
	pthread_mutex_unlock(&sim->table_lock);
	print_log(c, "has taken a dongle");
	print_log(c, "has taken a dongle");
	return (1);
}

void	release_both(t_coder *c)
{
	t_sim	*sim;
	long	until;

	sim = c->sim;
	until = get_time_ms() + sim->config.cooldown;
	pthread_mutex_lock(&sim->table_lock);
	c->left->is_taken = 0;
	c->right->is_taken = 0;
	c->left->available_at = until;
	c->right->available_at = until;
	pthread_cond_broadcast(&sim->table_cond);
	pthread_mutex_unlock(&sim->table_lock);
}
