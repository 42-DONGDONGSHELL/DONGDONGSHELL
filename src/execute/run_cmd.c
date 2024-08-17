/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drhee <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 16:18:05 by dongclee          #+#    #+#             */
/*   Updated: 2024/08/17 11:28:18 by drhee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ms_execute.h"
#include "../../include/ms_error.h"

char	*check_find_in_path(char *cmd, char **bin_paths)
{
	char	*bin_path;
	char	*tmp_path;
	int		i;

	i = 0;
	bin_path = NULL;
	while (bin_path == NULL && bin_paths[i])
	{
		tmp_path = ft_strjoin(bin_paths[i++], "/");
		bin_path = ft_strjoin(tmp_path, cmd);
		free(tmp_path);
		if (access(bin_path, F_OK) != 0)
		{
			free(bin_path);
			bin_path = NULL;
		}
	}
	return (bin_path);
}

/**
 * bin path 문자열 배열을 확인하며 해당 명령어가 수행 가능한지 찾고 경로를 반환 함.
 */
char	*find_executable_path(char *cmd, char **envp)
{
	char		**bin_paths;
	char		*bin_path;

	if (ft_strchr(cmd, '/'))
	{
		check_file_error(cmd);
		return (cmd);
	}
	bin_paths = get_bin_paths(envp);
	if (bin_paths == NULL)
	{
		check_file_error(cmd);
		return (cmd);
	}
	bin_path = check_find_in_path(cmd, bin_paths);
	free_arr(bin_paths);
	if (access(bin_path, F_OK) == 0 && access(bin_path, X_OK) != 0)
		exit(perror_no_permission(cmd));
	return (bin_path);
}

/**
 * 명령어의 실행 경로를 찾고 명령어 실행.
 */
int	search_cmd(t_token *token)
{
	char		*bin_path;

	if (token->cmd == NULL)
		exit(SUCCESS);
	bin_path = find_executable_path(token->cmd, *(token->envp));
	execve(bin_path, token->argv, *(token->envp));
	exit(perror_cmd_not_found(token->cmd));
}

/**
 * 빌트인 함수인지 확인 후 아니라면 실행 경로에 있는 함수인지 확인
 */
void	start_cmd(t_token *token, char *heredoc)
{
	int	ret;
	int	exit_code;

	ft_signal_default();
	exit_code = handle_redirection(token, heredoc);
	if (exit_code != 0)
		exit(exit_code);
	ret = is_builtin(token);
	if (ret != -1)
		exit_code = do_builtin(token, ret);
	else
		search_cmd(token);
	exit(exit_code);
}
