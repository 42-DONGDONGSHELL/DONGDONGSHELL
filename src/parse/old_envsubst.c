/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   old_envsubst.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drhee <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 21:07:16 by drhee             #+#    #+#             */
/*   Updated: 2024/08/01 22:25:19 by drhee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parse.h"

void	push_env_value(t_linkedlist *line_list, char *envp_value)
{
	int	j;

	j = 0;
	while (envp_value[j])
	{
		push(line_list, &(envp_value[j]));
		j++;
	}
}

int	is_valid_key_start(char c, t_linkedlist *line_list, int is_here_doc)
{
	char	*str;

	if (!(isalpha(c) || c == '_' || c == '?') && !is_here_doc)
	{
		free_linkedlist(line_list);
		return (0);
	}
	if (!(isalpha(c) || c == '_' || c == '?') && is_here_doc)
	{
		str = ft_strdup("$");
		push(line_list, str);
		return (0);
	}
	return (1);
}

int	push_envp(char **line, int *i, t_linkedlist *line_list, t_envp *envp_dict)
{
	t_linkedlist	*envp_key_list;
	char			*envp_key;
	char			*envp_value;

	if ((*line)[*i] == '?')
	{
		push(line_list, &(envp_dict->value[0]));
		(*i)++;
		return (0);
	}
	envp_key_list = create_linkedlist();
	while ((*line)[*i] && (isalnum((*line)[*i]) || (*line)[*i] == '_'))
	{
		push(envp_key_list, &((*line)[*i]));
		(*i)++;
	}
	envp_key = linkedlist_to_str(envp_key_list);
	free_linkedlist(envp_key_list);
	envp_value = find_envp_value(envp_dict, envp_key);
	safe_free((void **) &envp_key);
	if (!envp_value)
		return (0);
	push_env_value(line_list, envp_value);
	return (0);
}

char	*envsubst_heredoc(char *line, t_envp *envp_dict)
{
	t_linkedlist	*line_list;
	char			*envsubst_line;
	int				i;

	i = 0;
	line_list = create_linkedlist();
	while (line[i])
	{
		if (line[i] == '$')
		{
			if (!is_valid_key_start(line[++i], line_list, 1))
				continue ;
			push_envp(&line, &i, line_list, envp_dict);
		}
		else
			push(line_list, &(line[i++]));
	}
	envsubst_line = linkedlist_to_str(line_list);
	free_linkedlist(line_list);
	return (envsubst_line);
}

char	*envsubst(char *line, t_envp *envp_dict)
{
	t_linkedlist	*line_list;
	char			*envsubst_line;
	int				i;

	i = 0;
	line_list = create_linkedlist();
	while (line[i])
	{
		if ((line[i] == '$' && is_in_quotes(line, &(line[i])) != 1))
		{
			if (!is_valid_key_start(line[++i], line_list, 0))
				return (NULL);
			push_envp(&line, &i, line_list, envp_dict);
		}
		else if (line[i] == '~' && !is_in_quotes(line, &(line[i])))
		{
			push_env_value(line_list, find_envp_value(envp_dict, "HOME"));
			i++;
		}
		else
			push(line_list, &(line[i++]));
	}
	envsubst_line = linkedlist_to_str(line_list);
	free_linkedlist(line_list);
	return (envsubst_line);
}
