/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drhee <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 19:05:42 by drhee             #+#    #+#             */
/*   Updated: 2024/07/31 12:25:31 by drhee            ###   ########.fr       */
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

int	check_char_pos(const char *str, const char *target_addr, t_quote *quote)
{
	if (str == target_addr)
	{
		if (quote->s_quote)
			return (1);
		else if (quote->d_quote)
			return (2);
		else
			return (0);
	}
	return (-1);
}

int	is_in_quotes(const char *str, const char *target_addr)
{
	t_quote	quote;
	int		pos_check;

	quote.s_quote = 0;
	quote.d_quote = 0;
	while (*str != '\0')
	{
		if (*str == '\'' && !quote.d_quote)
		{
			quote.s_quote = !quote.s_quote;
			if (str == target_addr)
				return (1);
		}
		if (*str == '\"' && !quote.s_quote)
		{
			quote.d_quote = !quote.d_quote;
			if (str == target_addr)
				return (2);
		}
		pos_check = check_char_pos(str, target_addr, &quote);
		if (pos_check != -1)
			return (pos_check);
		str++;
	}
	return (0);
}
