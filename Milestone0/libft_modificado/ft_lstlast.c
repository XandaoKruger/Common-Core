/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acano-kr <acano-kr@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 14:29:08 by acano-kr          #+#    #+#             */
/*   Updated: 2026/04/23 14:35:33 by acano-kr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

/*#include <stdio.h>

int	main(void)
{
	t_list	*lst;
	t_list	*last;

	lst = ft_lstnew("a");
	lst->next = ft_lstnew("b");
	last = ft_lstlast(lst);
	printf("%s\n", (char *)last->content);
}*/
