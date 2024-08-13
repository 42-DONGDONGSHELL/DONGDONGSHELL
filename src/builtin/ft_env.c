/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongclee <dongclee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 16:13:48 by dongclee          #+#    #+#             */
/*   Updated: 2024/08/13 18:46:19 by dongclee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char *key_to_value_loc(char *key, char **envv)
{
	size_t	key_len;
	int i;

	key_len = ft_strlen(key);
	i = 0;
	while (envv[i])
	{
		if (ft_strncmp(envv[i], key, key_len) == 0 && envv[i][key_len] == '=')
			return (envv[i] + key_len + 1);
		i++;
	}
	return NULL;
}

int	ft_env(char **envv)
{
	int i;

	i = 0;
	while (envv[i])
	{
		ft_putendl_fd(envv[i], 1);
		i++;
	}
	return (SUCCESS);
}

int	execute_env(t_token *token)
{
	int	ret;

	ret = ft_env(*(token->envp));
	return (ret);
}
