/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acano-kr <acano-kr@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 09:45:36 by acano-kr          #+#    #+#             */
/*   Updated: 2026/04/22 17:17:27 by acano-kr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (!new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	new->next = *lst;
	*lst = new;
}

/* #include <stdio.h>

int	main(void)
{
	t_list	*a = ft_lstnew("Mazaki");
	t_list	*b = ft_lstnew("Takeo");
	

	ft_lstadd_front(&a, b);
	printf("%s\n", (char *)a->content);
} */
