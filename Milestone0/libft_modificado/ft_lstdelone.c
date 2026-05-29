/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acano-kr <acano-kr@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 19:42:44 by acano-kr          #+#    #+#             */
/*   Updated: 2026/04/22 19:42:44 by acano-kr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (!lst || !del)
		return ;
	del(lst->content);
	free(lst);
}

/* void	del(void *content)
{
	free(content);
}
int	main()
{
	t_list	*new = ft_lstnew(ft_strdup("FEIJÃO"));
	ft_lstdelone(new, &del);

	return (0);
} */
