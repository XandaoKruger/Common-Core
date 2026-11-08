/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acano-kr <acano-kr@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/07 11:53:48 by acano-kr          #+#    #+#             */
/*   Updated: 2026/11/08 20:58:10 by acano-kr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	main(void)
{
	long	a;
	int		i;

	a = get_time_ms();
	i = 0;
	while (i < 50)
	{
		ms_sleep(10);
		i++;
	}
	printf("50 x ms_sleep(10): %ld ms\n", get_time_ms() - a);
	return (0);
}
