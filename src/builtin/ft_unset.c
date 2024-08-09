/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongclee <dongclee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 16:13:58 by dongclee          #+#    #+#             */
/*   Updated: 2024/07/24 16:14:02 by dongclee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	migrate_except_deleted(char ***rtn, char **envp, char *del)
{
	int	i;
	int	j;
	int	del_len;

	i = 0;
	j = 0;
	del_len = ft_strlen(del);
	while (envp[i] != NULL) {
		if (ft_strncmp(envp[i], del, del_len) == 0 && envp[i][del_len] == '=') {
			i++;
			continue;
		}
		(*rtn)[j] = strdup(envp[i]);
		if ((*rtn)[j] == NULL) {
			while (--j >= 0)
				free((*rtn)[j]);
			free(*rtn);
			*rtn = NULL;
			return (ERROR);
		}
		i++;
		j++;
	}
	(*rtn)[j] = NULL;
	return (SUCCESS);
}

char	**create_new_envv(char **envp, char *del)
{
	char	**new;
	size_t	i;
	int	del_len;

	del_len = ft_strlen(del);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], del, del_len) == 0 && envp[i][del_len] == '=')
			continue;
		i++;
	}
	if (!(new = malloc(sizeof(char *) * (i + 1))))
		return (NULL);
	if (migrate_except_deleted(&new, envp, del) == ERROR)
	{
		free(new);
		return (NULL);
	}
	return (new);
}

void free_envv(char **envp) {
	size_t	i;

	i = 0;
	while (envp[i]) {
		free(envp[i]);
		i++;
	}
	free(envp);
}

int	execute_unset(t_token *token)
{
	char	**new_envv;
	int 	i;

	i = 1;
	while (token->argv[i])
	{
		if (!(new_envv = create_new_envv(token->envp, token->argv[i])))
			return (ERROR);
		free_envv(token->envp);
		token->envp = new_envv;
		i++;
	}
	return (SUCCESS);
}
