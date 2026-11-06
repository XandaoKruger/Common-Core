#ifndef CODEXION_H
# define CODEXION_H

// INCLUDES
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_sim	t_sim;

typedef struct e_sched
{
	FIFO,
	EDF
};	t_sched;

// read-only after parse: no mutex
typedef struct s_config
{
	long	coders;
	long	burnout;
	long	compile;
	long	debug;
	long	refractor;
	long	compiles_required;
	long	cooldown;
	t_sched sched;
};	t_config;


#endif