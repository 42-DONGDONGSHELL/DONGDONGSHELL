/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envsubst.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drhee <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 18:08:17 by drhee             #+#    #+#             */
/*   Updated: 2024/08/01 22:57:26 by drhee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parse.h"

void	push_env_value_to_list(t_linkedlist *line_list, char *envp_value)
{
	int	j;

	j = 0;
	while (envp_value[j])
	{
		push(line_list, &(envp_value[j]));
		j++;
	}
}

int	handle_dollar_expansion(char *line, int *i, t_linkedlist *line_list, t_envp *envp_dict)
{
	t_linkedlist	*envp_key_list;
	char			*envp_key;
	char			*envp_value;

	if (line[*i + 1] == '?')
	{
		push(line_list, &(envp_dict->value[0]));
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
			push_env_value_to_list(line_list, envp_value);
		return (1);
	}
	return (0);
}

int	handle_tilde_expansion(char *line, int *i, char *home, t_linkedlist *line_list, t_envp *envp_dict)
{
	char	*envp_value;

	envp_value = find_envp_value(envp_dict, "HOME");
	if (*i == 0 || is_whitespace(line[*i - 1]))
	{
		if (line[*i + 1] == '/' || line[*i + 1] == '\0' || is_whitespace(line[*i + 1]))
		{
			if (envp_value)
				push_env_value_to_list(line_list, envp_value);
			else
				push_env_value_to_list(line_list, home);
			(*i)++;
			return (1);
		}
	}
	return (0);
}

char	*envsubst(char *line, t_envp *envp_dict, char *home)
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
			if (handle_dollar_expansion(line, &i, line_list, envp_dict) == 1)
				continue ;
		}
		else if (line[i] == '~' && is_in_quotes(line, &(line[i])) == 0)
		{
			if (handle_tilde_expansion(line, &i, home, line_list, envp_dict) == 1)
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
			if (handle_dollar_expansion(line, &i, line_list, envp_dict) == 1)
				continue ;
		}
		push(line_list, &(line[i]));
		i++;
	}
	envsubst_line = linkedlist_to_str(line_list);
	free_linkedlist(line_list);
	return (envsubst_line);
}
