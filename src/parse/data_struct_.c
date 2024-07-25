/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_struct_.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drhee <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 16:37:08 by drhee             #+#    #+#             */
/*   Updated: 2024/07/25 19:21:57 by drhee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parse.h"

t_linkedlist	*create_linkedlist(void)
{
	t_linkedlist	*linkedlist;

	linkedlist = (t_linkedlist *)malloc(sizeof(t_linkedlist));
	if (!linkedlist)
		exit(EXIT_FAILURE);
	linkedlist->head = NULL;
	linkedlist->tail = NULL;
	linkedlist->size = 0;
	return (linkedlist);
}

t_node	*create_node(void *content)
{
	t_node	*new_node;

	new_node = (t_node *)malloc(sizeof(t_node));
	if (!new_node)
		exit(EXIT_FAILURE);
	new_node->content = content;
	new_node->prev = NULL;
	new_node->next = NULL;
	return (new_node);
}

void	push(t_linkedlist *linkedlist, void *content)
{
	t_node	*new_node;

	new_node = create_node(content);
	if (linkedlist->size == 0)
	{
		linkedlist->head = new_node;
		linkedlist->tail = new_node;
	}
	else
	{
		new_node->prev = linkedlist->tail;
		linkedlist->tail->next = new_node;
		linkedlist->tail = new_node;
	}
	linkedlist->size++;
}

void	*pop(t_linkedlist *linkedlist)
{
	void		*content;
	t_node		*pop_node;

	if (linkedlist->size == 0)
		return (NULL);
	content = linkedlist->tail->content;
	pop_node = linkedlist->tail;
	if (linkedlist->size == 1)
	{
		linkedlist->head = NULL;
		linkedlist->tail = NULL;
	}
	else
	{
		linkedlist->tail = pop_node->prev;
		linkedlist->tail->next = NULL;
	}
	free(pop_node);
	linkedlist->size--;
	return (content);
}
