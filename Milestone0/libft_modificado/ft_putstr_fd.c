/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acano-kr <acano-kr@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 18:56:18 by acano-kr          #+#    #+#             */
/*   Updated: 2026/04/17 18:56:18 by acano-kr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	write(fd, s, ft_strlen(s));
}

/* int	main(void)
{
	ft_putstr_fd("Black ops 2 é o melhor cod já feito!", 1);
	ft_putchar_fd('\n', 1);
	ft_putstr_fd("Isso é um erro", 2);
	ft_putchar_fd('\n', 2);
} */