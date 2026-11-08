/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acano-kr <acano-kr@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/07 11:53:48 by acano-kr          #+#    #+#             */
/*   Updated: 2026/11/08 19:36:07 by acano-kr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	main(void)
{
	long	a;
	long	b;

	a = get_time_ms();
	usleep(200000);
	b = get_time_ms();
	printf("a=%ld b=%ld diff=%ld\n", a, b, b - a);
	return (0);
}
