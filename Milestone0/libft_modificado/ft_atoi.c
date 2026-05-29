/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acano-kr <acano-kr@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 15:18:12 by acano-kr          #+#    #+#             */
/*   Updated: 2026/04/16 15:18:12 by acano-kr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(const char *str)
{
	int	i;
	int	res;
	int	sin;

	i = 0;
	sin = 1;
	res = 0;
	while ((str[i] == 32) || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sin = -sin;
		i++;
	}
	while ((str[i] >= '0' && str[i] <= '9') && str[i])
	{
		res = res * 10 + (str[i] - '0');
		i++;
	}
	return (res * sin);
}

/* #include <stdio.h>

int	main(void)
{
	char	a[] = "   -1234ab56";
	char	b[] = " \t\n\v -123";
	char	c[] = "--123";
	char	d[] = "++123";
	char	e[] = "Escola 42";
	char	f[] = "2147483647";
	char	g[] = "-2147483648";

	printf("Resultado: %d\n", ft_atoi(a));
	printf("Resultado: %d\n", ft_atoi(b));
	printf("Resultado: %d\n", ft_atoi(c));
	printf("Resultado: %d\n", ft_atoi(d));
	printf("Resultado: %d\n", ft_atoi(e));
	printf("Resultado: %d\n", ft_atoi(f));
	printf("Resultado: %d\n", ft_atoi(g));
} */
