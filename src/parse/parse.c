/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drhee <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 08:04:30 by drhee             #+#    #+#             */
/*   Updated: 2024/08/17 11:22:06 by drhee            ###   ########.fr       */
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

t_linkedlist	*substitute_env(t_linkedlist *trimmed_list, t_env *env)
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
			push(envsubst_list, envsubst((char *)now->content, env));
			envsubst_list->tail->type = now->type;
			safe_free((void **) &now->content);
		}
		now = now->next;
	}
	free_linkedlist(trimmed_list);
	return (envsubst_list);
}

void	remove_empty_node(t_linkedlist *list)
{
	t_node	*current;
	t_node	*next;

	current = list->head;
	while (current)
	{
		next = current->next;
		if (current->content && !ft_strncmp((char *)current->content, "\0", 1))
		{
			if (current == list->head)
				list->head = current->next;
			if (current == list->tail)
				list->tail = current->prev;
			if (current->prev)
				current->prev->next = current->next;
			if (current->next)
				current->next->prev = current->prev;
			safe_free((void **) &current->content);
			safe_free((void **) &current);
			list->size--;
		}
		current = next;
	}
}

int	parse(char *line, t_linkedlist **tk_list, char ***envp, t_env *env)
{
	t_linkedlist	*trimmed_list;
	t_linkedlist	*envsubst_list;
	t_node			*now;
	int				operator_check;

	if (!are_quotes_balanced(line))
		return (QUOTES);
	trimmed_list = parse_and_trim(line);
	operator_check = consecutive_operator_check(trimmed_list);
	if (operator_check)
		return (operator_check);
	env->envp_dict = create_envp_dict(*envp, env->exit_code);
	envsubst_list = substitute_env(trimmed_list, env);
	remove_empty_node(envsubst_list);
	*tk_list = create_token_list(envsubst_list, envp);
	replace_quotes(*tk_list);
	now = envsubst_list->head;
	while (now)
	{
		safe_free((void **) &now->content);
		now = now->next;
	}
	free_envp_dict(env->envp_dict);
	free_linkedlist(envsubst_list);
	return (ETC);
}
