/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_struct_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drhee <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 19:52:22 by drhee             #+#    #+#             */
/*   Updated: 2024/07/31 11:52:03 by drhee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/data_struct.h"

// free 필요
char	*linkedlist_to_str(t_linkedlist *linkedlist)
{
	char	*str;
	t_node	*node;
	int		i;

	str = (char *)safe_malloc(sizeof(char) * (linkedlist->size + 1));
	node = linkedlist->head;
	i = 0;
	while (node)
	{
		str[i] = *((char *)node->content);
		node = node->next;
		i++;
	}
	str[i] = '\0';
	return (str);
}

void	free_linkedlist(t_linkedlist *linkedlist)
{
	t_node	*head_node;
	t_node	*prev_node;
	int		i;

	if (linkedlist == NULL)
		return ;
	if (linkedlist->size == 0)
	{
		safe_free((void **) &linkedlist);
		return ;
	}
	head_node = linkedlist->head;
	i = 0;
	while (i < linkedlist->size)
	{
		prev_node = head_node->next;
		safe_free((void **) &head_node);
		head_node = prev_node;
		i++;
	}
	safe_free((void **) &(linkedlist->pid));
	safe_free((void **) &linkedlist);
}
