/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drhee <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 16:37:08 by drhee             #+#    #+#             */
/*   Updated: 2024/07/24 20:14:18 by drhee            ###   ########.fr       */
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
		linkedlist->tail->next = new_node;
		linkedlist->tail = new_node;
	}
	linkedlist->size++;
}

static t_node	*prev_tail_node(t_linkedlist *linkedlist)
{
	t_node	*prev;
	t_node	*current;

	prev = NULL;
	current = linkedlist->head;
	while (current->next != NULL)
	{
		prev = current;
		current = current->next;
	}
	return (prev);
}

void	*pop(t_linkedlist *linkedlist)
{
	t_node		*prev;
	t_node		*tail_node;
	void		*content;

	if (linkedlist->size == 0)
		return (NULL);
	prev = prev_tail_node(linkedlist);
	tail_node = linkedlist->tail;
	content = tail_node->content;
	if (linkedlist->size == 1)
	{
		linkedlist->head = NULL;
		linkedlist->tail = NULL;
	}
	else
	{
		prev->next = NULL;
		linkedlist->tail = prev;
	}
	free(tail_node);
	linkedlist->size--;
	return (content);
}
