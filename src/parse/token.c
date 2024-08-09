/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drhee <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 20:14:30 by drhee             #+#    #+#             */
/*   Updated: 2024/08/09 17:10:43 by drhee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parse.h"

int	array_size(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

char	**list_to_arr(t_linkedlist *linkedlist)
{
	t_node	*now;
	char	**arr;
	int		i;

	arr = (char **)safe_malloc(sizeof(char *) * (linkedlist->size + 1));
	now = linkedlist->head;
	i = 0;
	while (now)
	{
		arr[i] = now->content;
		now = now->next;
		i++;
	}
	arr[i] = NULL;
	return (arr);
}

void	push_argv(t_linkedlist *argv_list, char *str)
{
	int	i;
	int	start;

	start = 0;
	i = 0;
	while (str[i])
	{
		if (is_whitespace(str[i]) && !is_in_quotes(str, &str[i]))
		{
			push(argv_list, ft_substr(str, start, i - start));
			start = i + 1;
		}
		i++;
	}
	push(argv_list, ft_substr(str, start, i - start));
}

void	push_file(t_node **start, t_linkedlist *file_list)
{
	push(file_list, ft_strdup((*start)->content));
	file_list->tail->type = (*start)->type;
	push(file_list, ft_strdup((*start)->next->content));
	file_list->tail->type = (*start)->type;
	*start = (*start)->next;
}


void	create_token(t_node **start, t_node *now, t_linkedlist *token_list, char **envp)
{
	t_token			*token;
	t_linkedlist	*file_list;
	t_linkedlist	*argv_list;

	token = (t_token *)safe_malloc(sizeof(t_token));
	argv_list = create_linkedlist();
	file_list = create_linkedlist();
	while (*start != now)
	{
		if ((*start)->type != ETC)
			push_file(start, file_list);
		else if ((*start)->type == ETC)
			push_argv(argv_list, (*start)->content);
		*start = (*start)->next;
	}
	token->argv = list_to_arr(argv_list);
	token->argc = array_size(token->argv);
	token->cmd = token->argv[0];
	token->file_head = file_list->head;
	token->file_list = file_list;
	token->list_info = token_list;
	token->envp = envp;
	free_linkedlist(argv_list);
	push(token_list, token);
}

t_linkedlist	*create_token_list(t_linkedlist *envsubst_list, char **envp)
{
	t_node			*start;
	t_node			*now;
	t_linkedlist	*token_list;

	start = envsubst_list->head;
	now = envsubst_list->head;
	token_list = create_linkedlist();
	while (now)
	{
		if (now->type == PIPE)
		{
			create_token(&start, now, token_list, envp);
			start = now->next;
		}
		now = now->next;
	}
	create_token(&start, now, token_list, envp);
	return (token_list);
}
