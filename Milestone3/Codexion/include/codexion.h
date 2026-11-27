/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acano-kr <acano-kr@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/07 11:53:24 by acano-kr          #+#    #+#             */
/*   Updated: 2026/11/26 19:14:09 by acano-kr         ###   ########.fr       */
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
	pthread_mutex_t		table_lock;
	pthread_cond_t		table_cond;
	int					stop;
};

// FUNCTIONS

// PARSE.C ---------------------------------------------------------------------
int		parse_num(const char *s, long *out);
int		parse_sched(const char *s, t_sched *out);
int		parse_args(int argc, char **argv, t_config *cfg);
// -----------------------------------------------------------------------------

// TIME.C ----------------------------------------------------------------------
long	get_time_ms(void);
void	ms_sleep(long ms, t_sim *sim);
// -----------------------------------------------------------------------------

// LOG.C -----------------------------------------------------------------------
void	print_log(t_coder *coder, const char *msg);
int		is_stopped(t_sim *sim);
// -----------------------------------------------------------------------------

// INIT.C ----------------------------------------------------------------------
int		init_sim(t_sim *sim);
// -----------------------------------------------------------------------------

// CLEANUP.C -------------------------------------------------------------------
void	cleanup_sim(t_sim *sim);
// -----------------------------------------------------------------------------

// CODER.C ---------------------------------------------------------------------
void	*coder_routine(void *arg);
int		is_urgent(t_coder *c, long now);
// -----------------------------------------------------------------------------

// DONLGE.C --------------------------------------------------------------------
void	release_both(t_coder *c);
int		take_both(t_coder *coder);
// -----------------------------------------------------------------------------

// MONITOR.C -------------------------------------------------------------------
int		is_burned_out(t_coder *coder);
void	declare_burnout(t_coder *coder);
int		check_burnout(t_sim *sim);
void	*monitor_routine(void *arg);
// -----------------------------------------------------------------------------

//MONITOR_UTILS.C --------------------------------------------------------------
void	wake_dongles(t_sim *sim);
int		all_done(t_sim *sim);
void	stop_sim(t_sim *sim);
// -----------------------------------------------------------------------------

// HEAP.C ----------------------------------------------------------------------
int		heap_push(t_heap *h, t_req r);
int		heap_peek(t_heap*h, t_req *out);
int		heap_pop(t_heap *h, t_req *out);
void	heap_remove(t_heap *h, int id);
// -----------------------------------------------------------------------------

// HEAP_UTILS.C ----------------------------------------------------------------
int		req_less(t_req a, t_req b);
void	req_swap(t_req *a, t_req *b);
void	shift_up(t_heap *h, int i);
void	shift_down(t_heap *h, int i);
// -----------------------------------------------------------------------------

// DONGLE_QUEUE.C --------------------------------------------------------------
int		queue_request(t_dongle *d, t_coder *coder);
int		enqueue_both(t_coder *coder);
int		can_go(t_coder *coder, long now);
// -----------------------------------------------------------------------------

// LAUNCH.C --------------------------------------------------------------------
int		launch_coders(t_sim *sim);
// -----------------------------------------------------------------------------

#endif