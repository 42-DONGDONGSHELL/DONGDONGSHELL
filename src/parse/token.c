/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drhee <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 20:14:30 by drhee             #+#    #+#             */
/*   Updated: 2024/08/17 11:58:57 by drhee            ###   ########.fr       */
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

void	push_file(t_node **start, t_linkedlist *f_list, t_linkedlist *a_list)
{
	int		i;
	char	*file;

	i = 0;
	push(f_list, ft_safe_strdup((*start)->content));
	f_list->tail->type = (*start)->type;
	while (((char *)(*start)->next->content)[i] != '\0'
		&& !(((char *)(*start)->next->content)[i] == ' '
		&& !is_in_quotes((*start)->next->content, &((char *)(*start)->next->content)[i])))
		i++;
	file = safe_malloc(sizeof(char) * i + 1);
	ft_strlcpy(file, (*start)->next->content, i + 1);
	push(f_list, file);
	if (((char *)(*start)->next->content)[i++] == ' ')
		push_argv(a_list, &((char *)(*start)->next->content)[i]);
	f_list->tail->type = (*start)->next->type;
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
			push_file(start, file_list, argv_list);
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
			mk_token(&start, now, token_list, envp);
			start = now->next;
			token_list->token_cnt++;
		}
		now = now->next;
	}
	mk_token(&start, now, token_list, envp);
	token_list->token_cnt++;
	return (token_list);
}
