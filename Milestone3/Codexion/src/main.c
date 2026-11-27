/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acano-kr <acano-kr@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/07 11:53:48 by acano-kr          #+#    #+#             */
/*   Updated: 2026/11/25 12:47:17 by acano-kr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	main(int ac, char **av)
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
	if (!init_sim(&sim))
	{
		cleanup_sim(&sim);
		fprintf(stderr, "Error: initialization failed\n");
		return (1);
	}
	if (!launch_coders(&sim))
	{
		cleanup_sim(&sim);
		fprintf(stderr, "Error: thread creation failed\n");
		return (1);
	}
	cleanup_sim(&sim);
	return (0);
}
