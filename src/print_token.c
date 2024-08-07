/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drhee <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 17:51:09 by drhee             #+#    #+#             */
/*   Updated: 2024/08/07 21:36:49 by drhee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parse.h"

void	print_token(t_linkedlist *token_list)
{
	t_node	*now;
	t_token	*token;
	t_node	*file_now;
	int		i;

	now = token_list->head;
	while (now)
	{
		token = (t_token *)now->content;
		printf("cmd: %s\n", token->cmd);
		i = 0;
		while (token->argv[i])
		{
			printf("argv[%d]: %s\n", i, token->argv[i]);
			i++;
		}
		printf("argc: %d\n", token->argc);
		printf("envp: %s\n", token->envp[0].key);
		file_now = token->file_head;
		while (file_now)
		{
			printf("file: %s\n", (char *)file_now->content);
			file_now = file_now->next;
		}
		now = now->next;
	}
}
