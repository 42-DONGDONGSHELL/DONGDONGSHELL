/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drhee <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 11:11:48 by drhee             #+#    #+#             */
/*   Updated: 2024/08/12 11:29:13 by drhee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parse.h"

char	*trim_whitespace(const char	*str)
{
	const char	*start;
	const char	*end;
	char		*trimmed_str;
	size_t		new_length;

	if (str == NULL)
		return (NULL);
	start = str;
	end = str + ft_strlen(str) - 1;
	while (is_whitespace(*start))
		start++;
	while (end > start && is_whitespace(*end))
		end--;
	new_length = end - start + 1;
	trimmed_str = (char *)safe_malloc(new_length + 1);
	ft_strlcpy(trimmed_str, start, new_length + 1);
	return (trimmed_str);
}

t_linkedlist	*trim_list(t_linkedlist *parsed_list)
{
	t_linkedlist	*trimmed_list;
	t_node			*now;
	char			*trimmed_str;

	trimmed_list = create_linkedlist();
	now = parsed_list->head;
	while (now)
	{
		if (!is_str_whitespace((char *)now->content))
		{
			trimmed_str = trim_whitespace((char *)now->content);
			push(trimmed_list, trimmed_str);
			trimmed_list->tail->type = now->type;
		}
		safe_free((void **) &now->content);
		now = now->next;
	}
	return (trimmed_list);
}
