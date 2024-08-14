/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_struct_.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drhee <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 16:37:08 by drhee             #+#    #+#             */
/*   Updated: 2024/08/14 14:21:55 by drhee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/data_struct.h"

t_linkedlist	*create_linkedlist(void)
{
	t_linkedlist	*linkedlist;

	linkedlist = (t_linkedlist *)safe_malloc(sizeof(t_linkedlist));
	linkedlist->head = NULL;
	linkedlist->tail = NULL;
	linkedlist->size = 0;
	linkedlist->pid = NULL;
	linkedlist->token_cnt = 0;
	return (linkedlist);
}

t_node	*create_node(void *content)
{
	t_node	*new_node;

	new_node = (t_node *)safe_malloc(sizeof(t_node));
	new_node->content = content;
	new_node->prev = NULL;
	new_node->next = NULL;
	new_node->type = 0;
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
	safe_free((void **) &pop_node);
	linkedlist->size--;
	return (content);
}

void	*popleft(t_linkedlist *linkedlist)
{
	void		*content;
	t_node		*pop_node;

	if (linkedlist->size == 0)
		return (NULL);
	content = linkedlist->head->content;
	pop_node = linkedlist->head;
	if (linkedlist->size == 1)
	{
		linkedlist->head = NULL;
		linkedlist->tail = NULL;
	}
	else
	{
		linkedlist->head = pop_node->next;
		linkedlist->head->prev = NULL;
	}
	safe_free((void **) &pop_node);
	linkedlist->size--;
	return (content);
}
