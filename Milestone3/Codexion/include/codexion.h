/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acano-kr <acano-kr@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/07 11:53:24 by acano-kr          #+#    #+#             */
/*   Updated: 2026/11/08 15:19:32 by acano-kr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H

// INCLUDES
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>

// "STRUCTS"
typedef struct s_sim	t_sim;

typedef enum e_sched
{
	FIFO,
	EDF
}	t_sched;

// read-only after parse: no mutex
typedef struct s_config
{
	long				coders;
	long				burnout;
	long				compile;
	long				debug;
	long				refactor;
	long				compiles_required;
	long				cooldown;
	t_sched				sched;
}	t_config;

// key: fifo = arrival nbr, edf = deadline; coder_id breaks ties
typedef struct s_req
{
	long				key;
	int					coder_id;
}	t_req;

typedef struct s_heap
{
	t_req				*data;
	int					size;
	int					capacity;
}	t_heap;

// every field below "lock" is protected by "lock"
typedef struct s_dongle
{
	pthread_mutex_t		lock;
	pthread_cond_t		cond;
	int					is_taken;
	long				available_at;
	long				arrivals;
	t_heap				queue;
}	t_dongle;

/*
	id, left, right, sim: immutable after init.
	last_compile_start, compile_count: written by the coder,
	read by the monitor, protected by "lock"
*/
typedef struct s_coder
{
	int					id;
	pthread_t			thread;
	t_dongle			*left;
	t_dongle			*right;
	t_sim				*sim;
	pthread_mutex_t		lock;
	long				last_compile_start;
	int					compile_count;
}	t_coder;

// stop is protected by log_lock
struct s_sim
{
	t_config			config;
	long				start_time;
	t_coder				*coders;
	t_dongle			*dongles;
	pthread_t			monitor;
	pthread_mutex_t		log_lock;
	int					stop;
};

// FUNCTIONS

// PARSE.C
int	parse_num(const char *s, long *out);
int	parse_sched(const char *s, t_sched *out);
int	parse_args(int argc, char **argv, t_config *cfg);

#endif