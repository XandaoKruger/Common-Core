/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acano-kr <acano-kr@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/07 11:53:48 by acano-kr          #+#    #+#             */
/*   Updated: 2026/11/09 09:18:13 by acano-kr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

/* int	main(int ac, char **av)
{
	t_sim	sim;

	memset(&sim, 0, sizeof(sim));
	if (!parse_args(ac, av, &sim.config))
	{
		fprintf(stderr, "Usage: %s number_of_coders time_to_burnout "
			"time_to_compile time_to_debug time_to_refactor "
			"number_of_compiles_required dongle_cooldown "
			"scheduler(fifo|edf)\n", av[0]);
		return (1);
	}
	return (0);
} */

int	main(void)
{
	t_sim	sim;
	t_coder	c;

	memset(&sim, 0, sizeof(sim));
	memset(&c, 0, sizeof(c));
	pthread_mutex_init(&sim.log_lock, NULL);
	sim.start_time = get_time_ms();
	c.id = 1;
	c.sim = &sim;
	print_log(&c, "has taken a dongle");
	ms_sleep(200);
	print_log(&c, "is compiling");
	sim.stop = 1;
	print_log(&c, "is debugging");
	pthread_mutex_destroy(&sim.log_lock);
	return (0);
}
