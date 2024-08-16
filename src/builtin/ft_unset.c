/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongclee <dongclee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 16:13:58 by dongclee          #+#    #+#             */
/*   Updated: 2024/08/16 15:54:32 by dongclee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/ms_error.h"

int	is_valid_key(char *key)
{
	if (!ft_isalpha(*key) && *key != '_')
		return (0);
	key++;
	while (*key)
	{
		if (!ft_isalnum(*key) && *key != '_')
			return (FALSE);
		key++;
	}
	return (1);
}

void	migrate_except_deleted(char ***rtn, char **envp, char *del)
{
	int	i;
	int	j;
	int	del_len;

	i = 0;
	j = 0;
	del_len = ft_strlen(del);
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], del, del_len) == 0 && envp[i][del_len] == '=')
		{
			i++;
			continue ;
		}
		(*rtn)[j] = ft_safe_strdup(envp[i]);
		i++;
		j++;
	}
	(*rtn)[j] = NULL;
}

char	**create_new_envv(char **envp, char *del)
{
	char	**new;
	size_t	i;
	int		del_len;
	int		need_delete;

	del_len = ft_strlen(del);
	i = 0;
	need_delete = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], del, del_len) == 0 && envp[i][del_len] == '=')
			need_delete = 1;
		i++;
	}
	if (!need_delete)
		return (envp);
	new = (char **)safe_malloc(sizeof(char *) * (i + 1));
	migrate_except_deleted(&new, envp, del);
	return (new);
}

void	free_envv(char ***envp)
{
	size_t	i;

	i = 0;
	if ((*envp)[i] == NULL)
		return ;
	while ((*envp)[i])
	{
		free((*envp)[i]);
		i++;
	}
	free(*envp);
	*envp = NULL;
}

int	execute_unset(t_token *token)
{
	char	**new_envv;
	int		i;
	int		status;

	i = 1;
	status = SUCCESS;
	while (token->argv[i])
	{
		if (!is_valid_key(token->argv[i]))
		{
			status = perror_identifier("unset", token->argv[i++]);
			continue ;
		}
		new_envv = create_new_envv(*(token->envp), token->argv[i]);
		*(token->envp) = new_envv;
		i++;
	}
	return (status);
}
