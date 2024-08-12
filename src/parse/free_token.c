/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drhee <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 20:21:23 by drhee             #+#    #+#             */
/*   Updated: 2024/08/12 10:21:22 by drhee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parse.h"

void	free_token(t_token *token)
{
	int		i;
	t_node	*now;

	i = 0;
	while (token->argv[i])
	{
		safe_free((void **)&token->argv[i]);
		i++;
	}
	safe_free((void **)&token->argv);
	now = token->file_head;
	while (now)
	{
		safe_free((void **)&now->content);
		now = now->next;
	}
	free_linkedlist(token->file_list);
}

void	free_token_list(t_linkedlist *token_list)
{
	t_node	*now;

	now = token_list->head;
	while (now)
	{
		free_token((t_token *)now->content);
		safe_free((void **)&now->content);
		now = now->next;
	}
	free_linkedlist(token_list);
}
