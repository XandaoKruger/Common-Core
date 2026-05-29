/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bench.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dserra-d <dserra-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 09:08:29 by acano-kr          #+#    #+#             */
/*   Updated: 2026/05/28 09:38:36 by dserra-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

static char	*strategy_names(int s)
{
	if (s == FLAG_SIMPLE)
		return ("Simple / O(n^2)");
	if (s == FLAG_MEDIUM)
		return ("Medium / O(n*sqrt(n))");
	if (s == FLAG_COMPLEX)
		return ("Complex / O(n log n)");
	return ("Adaptive");
}

static void	print_sp(t_flags *flags)
{
	ft_putstr_fd("[bench] sa: ", 2);
	ft_putnbr_fd(flags->sa, 2);
	ft_putstr_fd("  sb: ", 2);
	ft_putnbr_fd(flags->sb, 2);
	ft_putstr_fd("  ss: ", 2);
	ft_putnbr_fd(flags->ss, 2);
	ft_putstr_fd("  pa: ", 2);
	ft_putnbr_fd(flags->pa, 2);
	ft_putstr_fd("  pb: ", 2);
	ft_putnbr_fd(flags->pb, 2);
	ft_putchar_fd('\n', 2);
}

static void	print_rotates(t_flags *flags)
{
	ft_putstr_fd("[bench] ra: ", 2);
	ft_putnbr_fd(flags->ra, 2);
	ft_putstr_fd("  rb: ", 2);
	ft_putnbr_fd(flags->rb, 2);
	ft_putstr_fd("  rr: ", 2);
	ft_putnbr_fd(flags->rr, 2);
	ft_putstr_fd("  rra: ", 2);
	ft_putnbr_fd(flags->rra, 2);
	ft_putstr_fd("  rrb: ", 2);
	ft_putnbr_fd(flags->rrb, 2);
	ft_putstr_fd("  rrr: ", 2);
	ft_putnbr_fd(flags->rrr, 2);
	ft_putchar_fd('\n', 2);
}

static void	print_disorder(float d)
{
	int	percent;
	int	decimal;

	percent = (int)(d * 100);
	decimal = (int)((d * 100.0f - percent) * 100);
	ft_putnbr_fd(percent, 2);
	ft_putchar_fd('.', 2);
	if (decimal < 10)
		ft_putchar_fd('0', 2);
	ft_putnbr_fd(decimal, 2);
	ft_putstr_fd("%\n", 2);
}

void	print_bench(t_flags *flags)
{
	int	total;
	int	rotates;
	int	reverse;

	total = flags->sa + flags->sb + flags->ss + flags->pa + flags->pb;
	rotates = flags->ra + flags->rb + flags->rr;
	reverse = flags->rra + flags->rrb + flags->rrr;
	total = total + rotates + reverse;
	ft_putstr_fd("[bench] disorder: ", 2);
	print_disorder(flags->disorder);
	ft_putstr_fd("[bench] strategy: ", 2);
	ft_putendl_fd(strategy_names(flags->used_strategy), 2);
	ft_putstr_fd("[bench] total_ops: ", 2);
	ft_putnbr_fd(total, 2);
	ft_putchar_fd('\n', 2);
	print_sp(flags);
	print_rotates(flags);
}
