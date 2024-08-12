/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drhee <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 11:18:13 by drhee             #+#    #+#             */
/*   Updated: 2024/08/12 11:23:33 by drhee            ###   ########.fr       */
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
			return_flag = 1;
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
