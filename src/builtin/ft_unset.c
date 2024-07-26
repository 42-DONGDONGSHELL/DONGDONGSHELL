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

void	migrate_except_deleted(char ***rtn, char **envp, char *del)
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
			return ;
		}
		i++;
		j++;
	}
	(*rtn)[j] = NULL;
}

char	**create_new_envv(char **envp, char *del, int *is_contained)
{
	char	**new;
	size_t	i;
	int	del_len;

	del_len = ft_strlen(del);
	i = 0;
	*is_contained = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], del, del_len) == 0 && envp[i][del_len] == '=')
			*is_contained = 1;
		i++;
	}
	if (!(new = malloc(sizeof(char *) * i)))
		return (NULL);
	migrate_except_deleted(&new, envp, del);
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

int	ft_unset(t_token *token)
{
	char	**new_envv;
	int 	is_contained;

	if (!token->argv[1])
		return (ERROR);
	if (!(new_envv = create_new_envv(token->envp, token->argv[1], &is_contained)))
		return (ERROR);
	if (is_contained == 0)
	{
		free_envv(new_envv);
		return (SUCCESS);
	}
	free_envv(token->envp);
	token->envp = new_envv;
	return (SUCCESS);
}
