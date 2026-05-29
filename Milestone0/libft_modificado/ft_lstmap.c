/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acano-kr <acano-kr@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 08:52:12 by acano-kr          #+#    #+#             */
/*   Updated: 2026/04/23 09:43:07 by acano-kr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*nova_lst;
	t_list	*novo_node;

	nova_lst = NULL;
	while (lst)
	{
		novo_node = ft_lstnew(f(lst->content));
		if (!novo_node)
		{
			ft_lstclear(&nova_lst, del);
			return (NULL);
		}
		ft_lstadd_back(&nova_lst, novo_node);
		lst = lst->next;
	}
	return (nova_lst);
}
/* void	*to_upper(void *content)
{
	char	*str = (char *)content;
	char	*new_str;
	int		i;

	new_str = ft_strdup(str);
	if (!new_str)
		return (NULL);

	i = 0;
	while (new_str[i])
	{
		new_str[i] = ft_toupper(new_str[i]);
		i++;
	}

	return (new_str);
}

void	del(void *content)
{
	free(content);
}

#include <stdio.h>

void	print_cont(void *content)
{
	printf("%s\n", (char *)content);
}

int main(void)
{
	t_list *original = NULL;
	t_list *nova_lista;

	ft_lstadd_back(&original, ft_lstnew(ft_strdup("Nuke")));
	ft_lstadd_back(&original, ft_lstnew(ft_strdup("Town")));

	nova_lista = ft_lstmap(original, to_upper, del);

	ft_lstiter(nova_lista, print_cont);

	ft_lstclear(&original, del);
	ft_lstclear(&nova_lista, del);
} */
