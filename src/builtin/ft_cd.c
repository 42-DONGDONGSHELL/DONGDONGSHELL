/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongclee <dongclee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 16:13:41 by dongclee          #+#    #+#             */
/*   Updated: 2024/07/31 12:35:19 by dongclee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtin.h"

int	ft_cd(char *path, char **envv)
{
	int	ret;
	char	*buf;
	char	*pwd;
	char	*old_pwd;

	if (!(buf = malloc(sizeof(char) * 1000)))
		return (ERROR);
	if(!getcwd(buf, sizeof(buf)))
		return (ERROR);
	ret = chdir(path);
	if (ret != 0)
		return (ERROR);
	old_pwd = ft_strjoin("PWD=", buf);
	if(!getcwd(buf, sizeof(buf)))
		return (ERROR);
	pwd = ft_strjoin("OLDPWD=", buf);
	ft_export(old_pwd, &envv);
	ft_export(pwd, &envv);
	free(buf);
	free(pwd);
	free(old_pwd);
	return (SUCCESS);
}

int	execute_cd(t_token *token)
{
	char	*path;

	if (token->argc == 1)
		path = key_to_value_loc("HOME", token->envp);
	else if (token->argv[1][0] =='\0')
		return (SUCCESS);
	else
		path = token->argv[1];
	if (ft_cd(path, token->envp) == ERROR)
	{
		// todo : Print error
		return (ERROR);
	}
	return (SUCCESS);
}
