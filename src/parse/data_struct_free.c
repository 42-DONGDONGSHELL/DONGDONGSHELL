/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_struct_free.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drhee <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 19:52:22 by drhee             #+#    #+#             */
/*   Updated: 2024/07/28 04:28:02 by drhee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parse.h"

void	free_linkedlist(t_linkedlist *linkedlist)
{
	t_node	*head_node;
	t_node	*prev_node;
	int		i;

	if (linkedlist == NULL)
		return ;
	if (linkedlist->size == 0)
	{
		safe_free((void**) &linkedlist);
		return ;
	}
	head_node = linkedlist->head;
	i = 0;
	while (i < linkedlist->size)
	{
		prev_node = head_node->next;
		safe_free((void**) &head_node);
		head_node = prev_node;
		i++;
	}
	safe_free((void**) &linkedlist);
}
