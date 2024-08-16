/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongclee <dongclee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 16:13:41 by dongclee          #+#    #+#             */
/*   Updated: 2024/08/16 16:27:09 by dongclee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ms_builtin.h"
#include "../../include/ms_error.h"

int	ft_cd(char *path, char ***envv)
{
	int		ret;
	char	*buf;
	char	*pwd;
	char	*old_pwd;

	buf = safe_malloc(sizeof(char) * 1000);
	if (!getcwd(buf, 1000))
		return (ERROR);
	ret = chdir(path);
	if (ret != 0)
	{
		free(buf);
		return (ERROR);
	}
	old_pwd = ft_strjoin("OLDPWD=", buf);
	if (!getcwd(buf, 1000))
		return (ERROR);
	pwd = ft_strjoin("PWD=", buf);
	ft_export(old_pwd, envv);
	ft_export(pwd, envv);
	free(buf);
	free(pwd);
	free(old_pwd);
	return (SUCCESS);
}

/**
 * cd, cd ~ : HOME
 * @param token
 * @return
 */
int	execute_cd(t_token *token)
{
	char	*path;

	if (token->argc == 1)
	{
		path = key_to_value_loc("HOME", *(token->envp));
		if (!path)
			return (perror_not_set("cd", "HOME"));
	}
	else if (ft_strncmp(token->argv[1], "", 2) == 0)
		return (SUCCESS);
	else if (ft_strncmp(token->argv[1], "-", 2) == 0)
	{
		path = key_to_value_loc("OLDPWD", *(token->envp));
		if (!path)
			return (perror_not_set("cd", "OLDPWD"));
	}
	else
		path = token->argv[1];
	if (ft_cd(path, token->envp) == ERROR)
		return (perror_cmd_arg("cd", path));
	return (SUCCESS);
}
