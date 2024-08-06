/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drhee <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 08:04:30 by drhee             #+#    #+#             */
/*   Updated: 2024/08/01 21:23:45 by drhee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parse.h"

t_linkedlist *trim_list(t_linkedlist *list)
{
	t_linkedlist	*new_list;
	t_node			*now;

	new_list = create_linkedlist();
	now = list->head;
	while (now)
	{
		if (*(char *)now->content != ' ')
			push(new_list, now->content);
		now = now->next;
	}
	return (new_list);
}

int	parse(char *line, char **envp, char *home)
{
	t_envp			*envp_dict;
	t_env_h			env_h;
	t_linkedlist	*parsed_list;
	t_linkedlist	*envsubst_list;
	t_node			*now;

	envp_dict = create_envp_dict(envp);
	env_h.envp_dict = envp_dict;
	env_h.home = home;
	parsed_list = parse_operator(line);
	envsubst_list = create_linkedlist();
	now = parsed_list->head;
	while (now)
	{

		if (!is_operator(*(char *)now->content))
		{
			push(envsubst_list, envsubst(now->content, &env_h));
			printf("token:%s\n", (char *)envsubst_list->tail->content);
		}
		else
		{
			push(envsubst_list, ft_strdup((char *)now->content));
			printf("operator:%s\n", (char *)envsubst_list->tail->content);
		}
		free(now->content);
		now = now->next;
	}
	now = envsubst_list->head;
	while (now)
	{
		free(now->content);
		now = now->next;
	}
	free_envp_dict(envp_dict);
	free_linkedlist(parsed_list);
	free_linkedlist(envsubst_list);
	return (0);
}
