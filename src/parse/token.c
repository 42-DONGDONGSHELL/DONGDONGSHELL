/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongclee <dongclee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 20:14:30 by drhee             #+#    #+#             */
/*   Updated: 2024/08/13 18:55:09 by dongclee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parse.h"

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
			push(argv_list, ft_safe_substr(str, start, i - start));
			start = i + 1;
		}
		i++;
	}
	push(argv_list, ft_safe_substr(str, start, i - start));
}

void	push_file(t_node **start, t_linkedlist *file_list)
{
	push(file_list, ft_safe_strdup((*start)->content));
	file_list->tail->type = (*start)->type;
	push(file_list, ft_safe_strdup((*start)->next->content));
	file_list->tail->type = (*start)->next->type;
	*start = (*start)->next;
}

void	mk_token(t_node **start, t_node *now, t_linkedlist *list, char ***envp)
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
	token->list_info = list;
	token->envp = envp;
	free_linkedlist(argv_list);
	push(list, token);
}

t_linkedlist	*create_token_list(t_linkedlist *envsubst_list, char ***envp)
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
			token_list->token_cnt++;
			mk_token(&start, now, token_list, envp);
			start = now->next;
		}
		now = now->next;
	}
	token_list->token_cnt++;
	mk_token(&start, now, token_list, envp);
	return (token_list);
}
