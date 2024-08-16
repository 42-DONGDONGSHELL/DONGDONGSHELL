/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongclee <dongclee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 16:18:05 by dongclee          #+#    #+#             */
/*   Updated: 2024/08/16 17:19:50 by dongclee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ms_execute.h"
#include "../../include/ms_error.h"
#include "../../include/ms_signal.h"

/**
 * 환경 변수 PATH를 읽어 bin경로들에 대한 문자열 배열을 반환함.
 */
char	**get_bin_paths(char **envp)
{
	char	*path;

	path = key_to_value_loc("PATH", envp);
	if (path == NULL)
		return (NULL);
	return (ft_split(path, ':'));
}

/**
 * 배열을 동적할당 free
 */
void	free_arr(char **arr)
{
	int	i;

	if (arr == NULL)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

/**
 * bin path 문자열 배열을 확인하며 해당 명령어가 수행 가능한지 찾고 경로를 반환 함.
 */
char	*find_executable_path(char *cmd, char **envp)
{
	char	**bin_paths;
	char	*bin_path;
	char	*tmp_path;
	int		i;

	bin_path = NULL;
	bin_paths = get_bin_paths(envp);
	if (bin_paths == NULL)
		return (NULL);
	if (access(cmd, F_OK) == 0)
		bin_path = ft_strdup(cmd);
	i = 0;
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
	free_arr(bin_paths);
	return (bin_path);
}

/**
 * 명령어의 실행 경로를 찾고 명령어 실행.
 */
int	search_cmd(t_token *token)
{
	char		*bin_path;
	struct stat	path_stat;

	bin_path = find_executable_path(token->cmd, *(token->envp));
	if (bin_path == NULL && token->file_head != NULL)
		exit(SUCCESS);
	if (bin_path == NULL)
		exit(perror_cmd_not_found(token->cmd));
	if (stat(bin_path, &path_stat) < 0)
		exit(perror_etc());
	if ((path_stat.st_mode & S_IFMT) == S_IFDIR)
		exit(perror_is_dir(bin_path));
	if (access(bin_path, X_OK) != 0)
		exit(perror_no_permission(bin_path));
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
