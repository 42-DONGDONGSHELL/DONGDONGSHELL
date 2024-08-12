/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drhee <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 08:04:30 by drhee             #+#    #+#             */
/*   Updated: 2024/08/12 11:57:58 by drhee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parse.h"

t_linkedlist	*parse_and_trim(char *line)
{
	t_linkedlist	*parsed_list;
	t_linkedlist	*trimmed_list;

	parsed_list = parse_operator(line);
	trimmed_list = trim_list(parsed_list);
	free_linkedlist(parsed_list);
	return (trimmed_list);
}

t_env_h	initialize_env(char **envp, char *h)
{
	t_envp	*envp_dict;
	t_env_h	env_h;

	envp_dict = create_envp_dict(envp);
	env_h.envp_dict = envp_dict;
	env_h.home = h;
	return (env_h);
}

t_linkedlist	*substitute_env(t_linkedlist *trimmed_list, t_env_h *env_h)
{
	t_linkedlist	*envsubst_list;
	t_node			*now;

	envsubst_list = create_linkedlist();
	now = trimmed_list->head;
	while (now)
	{
		if (now->prev && now->prev->type == HEREDOC)
		{
			push(envsubst_list, ft_safe_strdup((char *)now->content));
			envsubst_list->tail->type = now->type;
			safe_free((void **) &now->content);
		}
		else
		{
			push(envsubst_list, envsubst((char *)now->content, env_h));
			envsubst_list->tail->type = now->type;
			safe_free((void **) &now->content);
		}
		now = now->next;
	}
	free_linkedlist(trimmed_list);
	return (envsubst_list);
}

t_linkedlist	*parse(char *line, t_linkedlist *tk_list, char **envp, char *h)
{
	t_linkedlist	*trimmed_list;
	t_env_h			env_h;
	t_linkedlist	*envsubst_list;
	t_node			*now;

	if (!are_quotes_balanced(line))
		return (NULL);
	trimmed_list = parse_and_trim(line);
	if (consecutive_operator_check(trimmed_list))
		return (NULL);
	env_h = initialize_env(envp, h);
	envsubst_list = substitute_env(trimmed_list, &env_h);
	tk_list = create_token_list(envsubst_list, envp);
	replace_quotes(tk_list);
	now = envsubst_list->head;
	while (now)
	{
		safe_free((void **) &now->content);
		now = now->next;
	}
	free_envp_dict(env_h.envp_dict);
	free_linkedlist(envsubst_list);
	return (tk_list);
}
