/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acano-kr <acano-kr@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/07 11:53:45 by acano-kr          #+#    #+#             */
/*   Updated: 2026/11/09 11:33:04 by acano-kr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	print_log(t_coder *coder, const char *msg)
{
	pthread_mutex_lock(&coder->sim->log_lock);
	if (!coder->sim->stop)
		printf("%ld %d %s\n",
			get_time_ms() - coder->sim->start_time, coder->id, msg);
	pthread_mutex_unlock(&coder->sim->log_lock);
}
