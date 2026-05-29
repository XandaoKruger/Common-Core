/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dserra-d <dserra-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 16:49:08 by acano-kr          #+#    #+#             */
/*   Updated: 2026/05/28 09:46:39 by dserra-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

//INCLUDES======================================================================
# include "libft.h"

//DEFINE FLAGS==================================================================
# define FLAG_ADAPTIVE	0
# define FLAG_SIMPLE	1
# define FLAG_MEDIUM	2
# define FLAG_COMPLEX	3

//STRUCTS=======================================================================
typedef struct s_node
{
	int				value;
	int				index;
	int				rank;
	struct s_node	*next;
	struct s_node	*prev;
}	t_node;

typedef struct s_stack
{
	t_node	*top;
	t_node	*bottom;
	int		size;
}	t_stack;

typedef struct s_flags
{
	int		strategy;
	int		used_strategy;
	int		bench;
	float	disorder;
	int		sa;
	int		sb;
	int		ss;
	int		pa;
	int		pb;
	int		ra;
	int		rb;
	int		rr;
	int		rra;
	int		rrb;
	int		rrr;
}	t_flags;

typedef struct s_chunk
{
	int	min;
	int	max;
}	t_chunk;

//BENCH FUNCTIONS===============================================================
void		print_bench(t_flags *flags);

//PARSE FUNCTIONS===============================================================
int			*parse_args(char **args, int count, int *size);

//FLAGS FUNCTIONS===============================================================
int			get_flag(int argc, char **argv, t_flags *flags);
void		execute_strat(t_stack *stack_a, t_stack *stack_b, t_flags *flags);

//STACK FUNCTIONS===============================================================
void		ft_free_stack(t_stack *stack);
t_stack		*ft_init_stack(int *array, int size);
t_stack		*ft_init_empty(void);

//UTILS FUNCTION================================================================
long long	ft_atol(const char *str);
void		ft_free_args(char **args);
int			is_sorted(t_stack *stack);

//MAIN (PUSH_SWAP.C) FUNCTIONS==================================================
char		**init_program(int argc, char **argv, t_flags *flags, int *size);
int			setup_stacks(char **args, t_stack **a, t_stack **b, int size);
void		error(void);

//OPERATIONS FUNCTIONS==========================================================
void		swap(t_stack *s);
void		sa(t_stack *a, t_flags *flags);
void		sb(t_stack *b, t_flags *flags);
void		ss(t_stack *a, t_stack *b, t_flags *flags);
void		pa(t_stack *a, t_stack *b, t_flags *flags);
void		pb(t_stack *a, t_stack *b, t_flags *flags);
void		reverse(t_stack *s);
void		ra(t_stack *a, t_flags *flags);
void		rb(t_stack *b, t_flags *flags);
void		rr(t_stack *a, t_stack *b, t_flags *flags);
void		rotate(t_stack *s);
void		rra(t_stack *a, t_flags *flags);
void		rrb(t_stack *b, t_flags *flags);
void		rrr(t_stack *a, t_stack *b, t_flags *flags);

//ALGORITHM FUNCTIONS==========================================================
float		calculate_disorder(t_stack *a);
void		move_smallest_top(t_stack *a, t_flags *flags);
int			smallest_number(t_stack *a);
void		sort_simple(t_stack *a, t_stack *b, t_flags *flags);
void		set_index(t_stack *a);
void		sort_complex(t_stack *a, t_stack *b, t_flags *flags);
int			ft_sqrt(int n);
void		sort_medium(t_stack *a, t_stack *b, t_flags *flags);
void		move_index_top(t_stack *b, t_flags *flags);
int			biggest_index(t_stack *b);
int			chuck_position(t_stack *a, int min, int max);

#endif