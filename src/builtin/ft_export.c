/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongclee <dongclee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 16:13:55 by dongclee          #+#    #+#             */
/*   Updated: 2024/08/13 21:27:12 by dongclee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ms_builtin.h"
#include "../../include/ms_error.h"

int is_valid_env(const char *str)
{
	int	i;

	if (!str || !*str)
		return 0;
	i = 0;
	if (!ft_isalpha(str[i]) && str[i] != '_')
		return 0;
	i++;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return 0;
		i++;
	}
	if (str[i] != '=')
		return 0;
	return 1;
}

int is_same_env_key(const char *str, const char *envv)
{
	while (*str && *envv && *str != '=' && *envv != '=' && *str == *envv)
	{
		str++;
		envv++;
	}
	return *str == '=' && *envv == '=';
}

int	ft_export(char *str, char ***envv)
{
	int		i;
	char	**new_envv;

	if (!is_valid_env(str))
		return (perror_identifier("export", str)); // todo : 생각 필요함.
	i = -1;
	while ((*envv)[++i])
		if (is_same_env_key(str, (*envv)[i]))
		{
			free((*envv)[i]);
			(*envv)[i] = ft_strdup(str);
			return (SUCCESS);
		}
	new_envv = (char **)safe_malloc(sizeof(char *) * (i + 2));
	i = 0;
	while ((*envv)[i])
	{
		new_envv[i] = ft_strdup(envv[0][i]);
		i++;
	}
	new_envv[i++] = ft_strdup(str);
	new_envv[i] = NULL;
	free_envp(*envv);
	*envv = new_envv;
	return (SUCCESS);
}

int	execute_export(t_token *token)
{
	int	i;
	int	ret;

	ret = 0;
	if (token->argc == 1)
		ret = execute_env(token);
	i = 1;
	while (token->argv[i])
	{
		ret = ft_export(token->argv[i], token->envp);
		if (ret != 0)
			return (ret);
		i++;
	}
	 return (ret);
}
