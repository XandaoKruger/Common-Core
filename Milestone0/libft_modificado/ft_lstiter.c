/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acano-kr <acano-kr@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 08:10:28 by acano-kr          #+#    #+#             */
/*   Updated: 2026/04/23 08:33:17 by acano-kr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	if (!lst || !f)
		return ;
	while (lst)
	{
		f(lst->content);
		lst = lst->next;
	}
}

/* #include <stdio.h>

void	print_cont(void *content)
{
	printf("%s\n", (char *)content);
}

int	main(void)
{
	t_list *list = NULL;

	ft_lstadd_back(&list,ft_lstnew(ft_strdup("Primeiro")));
	ft_lstadd_back(&list,ft_lstnew(ft_strdup("Segundo")));
	ft_lstadd_back(&list,ft_lstnew(ft_strdup("Terceiro")));

	ft_lstiter(list, print_cont);
} */
