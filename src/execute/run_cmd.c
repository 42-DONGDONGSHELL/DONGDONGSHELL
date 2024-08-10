#include "../../include/execute.h"

/**
 * 환경 변수 PATH를 읽어 bin경로들에 대한 문자열 배열을 반환함.
 */
char **get_bin_paths(char **envp)
{
	char *path = key_to_value_loc("PATH", envp);
	if (path == NULL)
		return NULL;
	return ft_split(path, ':');
}

/**
 * 배열을 동적할당 free
 */
void free_arr(char **arr)
{
	int i;

	if (arr == NULL)
		return;
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
char *find_executable_path(char *cmd, char **envp)
{
	char	**bin_paths;
	char	*bin_path;
	char	*tmp_path;
	int		i;

	bin_path = NULL;
	if ((bin_paths = get_bin_paths(envp)) == NULL)
		return (NULL);
	if (access(cmd, F_OK) == 0)
		bin_path = ft_strdup(cmd);
	i = 0;
	while (bin_path == NULL && bin_paths[i])
	{
		tmp_path = ft_strjoin(bin_paths[i], "/");
		bin_path = ft_strjoin(tmp_path, cmd);
		free(tmp_path);
		if (access(bin_path, F_OK) != 0)
		{
			free(bin_path);
			bin_path = NULL;
		}
		i++;
	}
	free_arr(bin_paths);
	return (bin_path);
}

/**
 * 명령어의 실행 경로를 찾고 명령어 실행.
 */
int	search_cmd(t_token *token)
{
	char	*bin_path;

	bin_path = find_executable_path(token->cmd, token->envp);
	if (bin_path == NULL)
		return (ERROR); // todo : print Error cmd not found
	execve(bin_path, token->argv, token->envp);
	// todo : print Error cmd not found
	exit(127);
}

/**
 * 빌트인 함수인지 확인 후 아니라면 실행 경로에 있는 함수인지 확인
 */
void	start_cmd(t_token *token, char *heredoc)
{
	int	ret;
	int	exit_code;

	if (token->cmd[0] == '\0')
		exit(0);
	if (handle_redirection(token, heredoc))
		exit(1);
	if ((ret = is_builtin(token)) != -1)
		exit_code = do_builtin(token, ret);
	else
		exit_code = search_cmd(token);
	exit(exit_code);
}
