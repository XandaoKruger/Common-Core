/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acano-kr <acano-kr@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 16:24:14 by acano-kr          #+#    #+#             */
/*   Updated: 2026/04/28 10:52:11 by acano-kr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*node;

	if (!new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	node = ft_lstlast(*lst);
	node->next = new;
}

/* #include <stdio.h>

int	main(void)
{
	t_list *no = NULL;
	t_list *novo = ft_lstnew(ft_strdup("Samantha Maxis")); //Strudp garante que
														// o no e dono da 
														//propria memoria
	printf("%s\n", (char *)no->content);
	free(novo);		//Dar free porque strdup usa malloc e por isso ele tem sua
					//propria memoria.
} */
