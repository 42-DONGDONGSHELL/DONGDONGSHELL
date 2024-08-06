/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drhee <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 20:14:30 by drhee             #+#    #+#             */
/*   Updated: 2024/08/06 22:21:30 by drhee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parse.h"

t_linkedlist	*split_argv_list(char *str)
{
	t_linkedlist	*argv_list;
	int				i;
	int				start;

	argv_list = create_linkedlist();
	start = 0;
	i = 0;
	while (str[i])
	{
		if (is_whitespace(str[i]) && is_in_quotes(str, &str[i]))
		{
			push(argv_list, ft_substr(str, start, i - start));
			start = i + 1;
		}
		i++;
	}
	push(argv_list, ft_substr(str, start, i - start));
	return (argv_list);
}

char **split_argv(char *str)
{
	t_linkedlist	*argv_list;
	char			**argv;
	t_node			*now;
	int				i;

	argv_list = split_argv_list(str);
	argv = (char **)safe_malloc(sizeof(char *) * (argv_list->size + 1));
	i = 0;
	now = argv_list->head;
	while (now)
	{
		argv[i] = now->content;
		now = now->next;
		i++;
	}
	argv[i] = NULL;
	free_linkedlist(argv_list);
	return (argv);
}

void	create_token(t_node **start, t_node *now, t_linkedlist *token_list)
{
	t_token			*token;
	t_linkedlist	*file_list;

	token = (t_token *)safe_malloc(sizeof(t_token));
	file_list = create_linkedlist();
	while (*start != now)
	{
		if ((*start)->type != ETC)
		{
			push(file_list, (*start)->content);
			file_list->tail->type = (*start)->type;
		}
		else if ((*start)->type == ETC)
		{
			token->argv = split_argv((*start)->content);
			token->argc = file_list->size;
			token->cmd = split_argv((*start)->content)[0];
		}
		*start = (*start)->next;
	}
	token->file_list = file_list->head;
	token->list_info = token_list;
	push(token_list, token);
}

t_linkedlist *token_list(t_linkedlist *envsubst_list, t_envp *envp)
{
	t_node *start;
	t_node *now;
	t_linkedlist *token_list;

	start = envsubst_list->head;
	now = envsubst_list->head;
	token_list = create_linkedlist();
	while (now)
	{
		if (now->type == PIPE)
			create_token(&start, now, token_list);
		now = now->next;
		start = now;
	}
	create_token(&start, now, token_list);
	return (token_list);
}
