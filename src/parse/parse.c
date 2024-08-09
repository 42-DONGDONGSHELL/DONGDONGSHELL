/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drhee <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 08:04:30 by drhee             #+#    #+#             */
/*   Updated: 2024/08/09 19:22:28 by drhee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parse.h"

char	*trim_whitespace(const char* str)
{
	const char* start;
	const char* end;
	char* trimmed_str;
	size_t new_length;

	if (str == NULL)
		return NULL;
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
	}
	return (return_flag);
}


t_linkedlist	*parse(char *line, t_linkedlist *token_list,char **envp, char *home)
{
	t_envp			*envp_dict;
	t_env_h			env_h;
	t_linkedlist	*parsed_list;
	t_linkedlist	*trimmed_list;
	t_linkedlist	*envsubst_list;
	t_node			*now;

	if (!are_quotes_balanced(line))
		return (NULL);
	parsed_list = parse_operator(line);
	trimmed_list = trim_list(parsed_list);
	free_linkedlist(parsed_list);
	if (consecutive_operator_check(trimmed_list))
	{
		free_linkedlist(trimmed_list);
		return (NULL);
	}
	envp_dict = create_envp_dict(envp);
	env_h.envp_dict = envp_dict;
	env_h.home = home;
	envsubst_list = create_linkedlist();
	now = trimmed_list->head;
	while (now)
	{
		if (now->prev && now->prev->type == HEREDOC)
		{
			push(envsubst_list, ft_safe_strdup((char *)now->content));
			envsubst_list->tail->type = now->type;
			safe_free((void **) &now->content);
			now = now->next;
		}
		else
		{
			push(envsubst_list, envsubst((char *)now->content, &env_h));
			envsubst_list->tail->type = now->type;
			safe_free((void **) &now->content);
			now = now->next;
		}
	}
	free_linkedlist(trimmed_list);
	token_list = create_token_list(envsubst_list, envp);
	print_token(token_list);
	now = envsubst_list->head;
	while (now)
	{
		safe_free((void **) &now->content);
		now = now->next;
	}
	free_envp_dict(envp_dict);
	free_linkedlist(envsubst_list);
	return (token_list);
}
