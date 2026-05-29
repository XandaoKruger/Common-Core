/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acano-kr <acano-kr@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 11:46:14 by acano-kr          #+#    #+#             */
/*   Updated: 2026/04/11 11:46:14 by acano-kr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (unsigned char)c)
			return ((char *)&s[i]);
		i++;
	}
	if (!(unsigned char)c)
		return ((char *)&s[i]);
	return (0);
}
/* #include <stdio.h>

int	main(void)
{
	char	a[] = "banana";
	int	b = 'a';
	char *result = ft_strchr(a, b);

	if (result)
		printf("%s\n", result);
	else
		printf("não encontrado\n");
} */