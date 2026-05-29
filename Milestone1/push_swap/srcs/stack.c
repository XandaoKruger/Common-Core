/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dserra-d <dserra-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 15:30:24 by acano-kr          #+#    #+#             */
/*   Updated: 2026/05/25 09:58:49 by dserra-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

static t_node	*ft_new_node(int value)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	node->value = value;
	node->index = 0;
	node->rank = 0;
	node->prev = NULL;
	node->next = NULL;
	return (node);
}

static void	ft_add_botom(t_node **list, t_node *new)
{
	t_node	*n1;

	if (!new)
		return ;
	if (!*list)
	{
		*list = new;
		return ;
	}
	n1 = *list;
	while (n1->next)
		n1 = n1->next;
	n1->next = new;
	new->prev = n1;
}

void	ft_free_stack(t_stack *stack)
{
	t_node	*temp;
	t_node	*current;

	current = stack->top;
	while (current)
	{
		temp = current->next;
		free(current);
		current = temp;
	}
	free(stack);
}

t_stack	*ft_init_empty(void)
{
	t_stack	*empty;

	empty = malloc(sizeof(t_stack));
	if (!empty)
		return (NULL);
	empty->top = NULL;
	empty->bottom = NULL;
	empty->size = 0;
	return (empty);
}

t_stack	*ft_init_stack(int *array, int size)
{
	t_stack	*stack;
	int		i;
	t_node	*novo;

	stack = malloc(sizeof(t_stack));
	if (!stack)
		return (NULL);
	stack->top = NULL;
	stack->bottom = NULL;
	stack->size = 0;
	i = 0;
	while (i < size)
	{
		novo = ft_new_node(array[i]);
		ft_add_botom(&stack->top, novo);
		stack->bottom = novo;
		stack->size++;
		i++;
	}
	return (stack);
}
