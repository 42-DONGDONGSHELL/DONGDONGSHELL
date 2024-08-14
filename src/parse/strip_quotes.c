/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strip_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drhee <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 20:10:01 by drhee             #+#    #+#             */
/*   Updated: 2024/08/12 11:54:11 by drhee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parse.h"

void	push_char_to_list(char *str, int *i, t_linkedlist *str_list)
{
	char	*c;

	c = safe_malloc(sizeof(char) * 2);
	*c = str[*i];
	*(c + 1) = '\0';
	push(str_list, c);
}

void	process_quotes(char *str, int *i, t_linkedlist *str_list, char quote)
{
	(*i)++;
	while (str[*i] && str[*i] != quote)
	{
		push_char_to_list(str, i, str_list);
		(*i)++;
	}
}

char	*strip_quotes(char *str)
{
	t_linkedlist	*str_list;
	t_node			*node;
	char			*new_str;
	int				i;

	i = 0;
	str_list = create_linkedlist();
	while (str[i])
	{
		if ((str[i] == '\'' && is_in_quotes(str, &str[i]) == 1) \
			|| (str[i] == '\"' && is_in_quotes(str, &str[i]) == 2))
			process_quotes(str, &i, str_list, str[i]);
		else
			push_char_to_list(str, &i, str_list);
		i++;
	}
	new_str = linkedlist_to_str(str_list);
	node = str_list->head;
	while (node)
	{
		safe_free((void **)&node->content);
		node = node->next;
	}
	free_linkedlist(str_list);
	return (new_str);
}

void	replace_quotes_in_token(t_token *token)
{
	int		i;
	char	*new_str;
	t_node	*now_file;

	i = 0;
	while (token->argv[i])
	{
		new_str = strip_quotes(token->argv[i]);
		safe_free((void **)&token->argv[i]);
		token->argv[i++] = new_str;
	}
	token->cmd = token->argv[0];
	now_file = token->file_head;
	while (now_file)
	{
		if (now_file->type == HEREDOC)
		{
			now_file = now_file->next->next;
			continue;
		}
		new_str = strip_quotes(now_file->content);
		safe_free((void **)&now_file->content);
		now_file->content = new_str;
		now_file = now_file->next;
	}
}

void	replace_quotes(t_linkedlist *token_list)
{
	t_node	*now;

	now = token_list->head;
	while (now)
	{
		replace_quotes_in_token(now->content);
		now = now->next;
	}
}
