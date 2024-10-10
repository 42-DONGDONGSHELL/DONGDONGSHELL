/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongclee <dongclee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 16:13:41 by dongclee          #+#    #+#             */
/*   Updated: 2024/10/10 18:54:44 by dongclee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ms_builtin.h"
#include "../../include/ms_error.h"

int	ft_cd(char *path, char ***envv)
{
	int	ret;
	char	*buf;
	char	*pwd;
	char	*old_pwd;

	buf_pwd = key_to_value_loc("PWD", *envv);
	if (chdir(path) != 0)
		return (ERROR);
	old_pwd = ft_strjoin("OLDPWD=", buf_pwd);
	buf = safe_malloc(sizeof(char) * 1000);
	if (!getcwd(buf, 1000))
	{
		ft_putstr_fd("cd: error retrieving current directory: getcwd: ", 1);
		ft_putstr_fd("cannot access parent directories: ", 1);
		ft_putendl_fd("No such file or directory", 1);
	}
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
