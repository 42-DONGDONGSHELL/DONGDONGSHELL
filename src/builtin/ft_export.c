/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongclee <dongclee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 16:13:55 by dongclee          #+#    #+#             */
/*   Updated: 2024/08/16 17:16:33 by dongclee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ms_builtin.h"
#include "../../include/ms_error.h"

int	is_valid_env(const char *str)
{
	int	i;

	if (!str || !*str)
		return (0);
	i = 0;
	if (!ft_isalpha(str[i]) && str[i] != '_')
		return (0);
	i++;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	is_same_env_key(const char *str, const char *envv)
{
	while (*str && *envv && *str != '=' && *envv != '=' && *str == *envv)
	{
		str++;
		envv++;
	}
	if ((*envv == '\0' || *envv == '=') && (*str == '\0' || *str == '='))
		return (1);
	return (0);
}

char	**malloc_new_envv(char **envv, char *str, int size)
{
	char	**new_envv;
	int		i;

	new_envv = (char **)safe_malloc(sizeof(char *) * (size + 2));
	i = -1;
	while (envv[++i])
		new_envv[i] = ft_safe_strdup(envv[i]);
	new_envv[i++] = ft_safe_strdup(str);
	new_envv[i] = NULL;
	return (new_envv);
}

int	ft_export(char *str, char ***envv)
{
	int		i;
	char	**new_envv;

	if (!is_valid_env(str))
		return (perror_identifier("export", str));
	i = -1;
	while ((*envv)[++i])
	{
		if (is_same_env_key(str, (*envv)[i]))
		{
			if (!is_declared(str))
				return (SUCCESS);
			free((*envv)[i]);
			(*envv)[i] = ft_strdup(str);
			return (SUCCESS);
		}
	}
	new_envv = malloc_new_envv(*envv, str, i);
	free_envp(*envv);
	*envv = new_envv;
	return (SUCCESS);
}

int	execute_export(t_token *token)
{
	int	i;
	int	ret;
	int	status;

	status = SUCCESS;
	if (token->argc == 1)
		print_all_env(*(token->envp));
	i = 1;
	while (token->argv[i])
	{
		ret = ft_export(token->argv[i], token->envp);
		if (ret != 0)
			status = ret;
		i++;
	}
	return (status);
}
