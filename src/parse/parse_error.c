/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drhee <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 11:18:13 by drhee             #+#    #+#             */
/*   Updated: 2024/08/12 17:38:41 by drhee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parse.h"

int	are_quotes_balanced(const char *str)
{
	t_quote	quote;

	quote.s_quote = 0;
	quote.d_quote = 0;
	while (*str != '\0')
	{
		if (*str == '\'' && !quote.d_quote)
			quote.s_quote = !quote.s_quote;
		else if (*str == '\"' && !quote.s_quote)
			quote.d_quote = !quote.d_quote;
		str++;
	}
	if (!quote.s_quote && !quote.d_quote)
		return (1);
	return (0);
}

int	set_return_flag(t_node *now)
{
	if (now->type == PIPE)
		return (PIPE);
	else if (now->next == NULL)
		return (NEWLINE);
	else
		return (now->next->type);
}

int	consecutive_operator_check(t_linkedlist *trimmed_list)
{
	t_node	*now;
	int		return_flag;

	return_flag = 0;
	now = trimmed_list->head;
	while (now)
	{
		if ((now->type != 0) && (now->next == NULL || now->next->type != 0))
		{
			return_flag = set_return_flag(now);
			break ;
		}
		now = now->next;
	}
	now = trimmed_list->head;
	if (return_flag)
	{
		while (now)
		{
			safe_free((void **) &now->content);
			now = now->next;
		}
		free_linkedlist(trimmed_list);
	}
	return (return_flag);
}

void	print_parse_error(int error_code)
{
	if (error_code == QUOTES)
		printf("minishell: syntax error: unexpected end of file\n");
	else if (error_code == PIPE)
		printf("minishell: syntax error: unexpected token `|'\n");
	else if (error_code == NEWLINE)
		printf("minishell: syntax error: unexpected newline\n");
	else if (error_code == OUTPUT)
		printf("minishell: syntax error: unexpected token `>'\n");
	else if (error_code == APPEND_OUTPUT)
		printf("minishell: syntax error: unexpected token `>>'\n");
	else if (error_code == INPUT)
		printf("minishell: syntax error: unexpected token `<'\n");
	else if (error_code == HEREDOC)
		printf("minishell: syntax error: unexpected token `<<'\n");
}
