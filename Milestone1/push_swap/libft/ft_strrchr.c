/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acano-kr <acano-kr@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 14:54:05 by acano-kr          #+#    #+#             */
/*   Updated: 2026/04/11 14:54:05 by acano-kr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	while (i >= 0 && s[i] != (unsigned char)c)
		i--;
	if (i < 0)
		return (0);
	return ((char *)&s[i]);
}

/* #include <stdio.h>

int	main(void)
{
	char	a[] = "banane";
	int	b = 'a';
	char *result = ft_strrchr(a, b);

	if (result)
		printf("%s\n", result);
	else
		printf("não encontrado\n");
} */
