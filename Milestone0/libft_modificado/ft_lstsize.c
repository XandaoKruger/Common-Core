/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acano-kr <acano-kr@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 11:58:06 by acano-kr          #+#    #+#             */
/*   Updated: 2026/04/22 14:22:30 by acano-kr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	i;

	i = 0;
	if (!lst)
		return (0);
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

/* #include <stdio.h>

int	main(void)
{
	t_list	*list = NULL;
	t_list	*new = ft_lstnew("Teste");
	t_list	*new1 = ft_lstnew("Oto teste");

	ft_lstadd_front(&list, new);
	ft_lstadd_front(&list, new1);
	printf("%d\n", ft_lstsize(list));
} */
