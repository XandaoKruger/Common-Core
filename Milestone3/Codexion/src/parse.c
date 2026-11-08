/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acano-kr <acano-kr@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/07 11:53:52 by acano-kr          #+#    #+#             */
/*   Updated: 2026/11/08 12:36:49 by acano-kr         ###   ########.fr       */
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

/* int	parse_args(int argc, char **argv, t_config *cfg)
{
	
} */