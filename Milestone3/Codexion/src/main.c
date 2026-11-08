/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acano-kr <acano-kr@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/07 11:53:48 by acano-kr          #+#    #+#             */
/*   Updated: 2026/11/08 15:30:28 by acano-kr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	main(int ac, char **av)
{
	t_config	cfg;
	int			r;

	r = parse_args(ac, av, &cfg);
	printf("ret=%d\n", r);
	if (!r)
		return (1);
	printf("%ld %ld %ld %ld\n", cfg.coders, cfg.burnout,
		cfg.compile, cfg.debug);
	printf("%ld %ld %ld %d\n", cfg.refactor,
		cfg.compiles_required, cfg.cooldown, cfg.sched);
	return (0);
}
