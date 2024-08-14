/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envsubst.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drhee <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 17:34:18 by drhee             #+#    #+#             */
/*   Updated: 2024/08/14 15:49:51 by drhee            ###   ########.fr       */
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

int	expand_dlr(char *line, int *i, t_linkedlist *line_list, t_envp *envp_dict)
{
	t_linkedlist	*envp_key_list;
	char			*envp_key;
	char			*envp_value;

	if (line[*i + 1] == '?')
	{
		push_env_value(line_list, &(envp_dict->value[0]));
		*i = *i + 2;
		return (1);
	}
	else if (ft_isalpha(line[*i + 1]) || line[*i + 1] == '_')
	{
		(*i)++;
		envp_key_list = create_linkedlist();
		while (line[*i] && (ft_isalnum(line[*i]) || line[*i] == '_'))
			push(envp_key_list, &(line[(*i)++]));
		envp_key = linkedlist_to_str(envp_key_list);
		free_linkedlist(envp_key_list);
		envp_value = find_envp_value(envp_dict, envp_key);
		safe_free((void **) &envp_key);
		if (envp_value)
			push_env_value(line_list, envp_value);
		return (1);
	}
	return (0);
}

int	expand_tld(char *line, int *i, t_linkedlist *line_list, t_env *env_h)
{
	char	*envp_value;

	envp_value = find_envp_value(env_h->envp_dict, "HOME");
	if (*i == 0 || is_whitespace(line[*i - 1]))
	{
		if (line[*i + 1] == '/' || line[*i + 1] == '\0' \
			|| is_whitespace(line[*i + 1]))
		{
			if (envp_value)
				push_env_value(line_list, envp_value);
			else
				push_env_value(line_list, env_h->home);
			(*i)++;
			return (1);
		}
	}
	return (0);
}

char	*envsubst(char *line, t_env *env)
{
	t_linkedlist	*line_list;
	char			*envsubst_line;
	int				i;

	i = 0;
	line_list = create_linkedlist();
	while (line[i])
	{
		if (line[i] == '$' && is_in_quotes(line, &(line[i])) != 1)
		{
			if (expand_dlr(line, &i, line_list, env->envp_dict) == 1)
				continue ;
		}
		else if (line[i] == '~' && is_in_quotes(line, &(line[i])) == 0)
		{
			if (expand_tld(line, &i, line_list, env) == 1)
				continue ;
		}
		push(line_list, &(line[i]));
		i++;
	}
	envsubst_line = linkedlist_to_str(line_list);
	free_linkedlist(line_list);
	return (envsubst_line);
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
			if (expand_dlr(line, &i, line_list, envp_dict) == 1)
				continue ;
		}
		push(line_list, &(line[i]));
		i++;
	}
	envsubst_line = linkedlist_to_str(line_list);
	free_linkedlist(line_list);
	return (envsubst_line);
}
