/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acano-kr <acano-kr@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/07 11:53:52 by acano-kr          #+#    #+#             */
/*   Updated: 2026/11/08 15:31:49 by acano-kr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	parse_num(const char *s, long *out)
{
	int	i;
	int	value;
	int	d;

	if (!s || !s[0])
		return (0);
	i = 0;
	value = 0;
	while (s[i])
	{
		if (!(s[i] >= '0' && s[i] <= '9'))
			return (0);
		d = (s[i] - '0');
		if (value > (INT_MAX - d) / 10)
			return (0);
		value = (value * 10) + d;
		i++;
	}
	*out = value;
	return (1);
}

int	parse_sched(const char *s, t_sched *out)
{
	if (!s)
		return (0);
	if (strcmp(s, "fifo") == 0)
	{
		*out = FIFO;
		return (1);
	}
	if (strcmp(s, "edf") == 0)
	{
		*out = EDF;
		return (1);
	}
	return (0);
}

int	parse_args(int ac, char **av, t_config *cfg)
{
	if (ac != 9)
		return (0);
	if (!parse_num(av[1], &cfg->coders))
		return (0);
	if (!parse_num(av[2], &cfg->burnout))
		return (0);
	if (!parse_num(av[3], &cfg->compile))
		return (0);
	if (!parse_num(av[4], &cfg->debug))
		return (0);
	if (!parse_num(av[5], &cfg->refactor))
		return (0);
	if (!parse_num(av[6], &cfg->compiles_required))
		return (0);
	if (!parse_num(av[7], &cfg->cooldown))
		return (0);
	if (!parse_sched(av[8], &cfg->sched))
		return (0);
	if (cfg->coders < 1 || cfg->burnout < 1)
		return (0);
	return (1);
}
