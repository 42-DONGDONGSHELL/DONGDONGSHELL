/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cmd_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongclee <dongclee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 16:18:05 by dongclee          #+#    #+#             */
/*   Updated: 2024/08/16 17:19:50 by dongclee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ms_execute.h"
#include "../../include/ms_error.h"

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

void	check_file_error(char *path)
{
	struct stat	path_stat;

	if (access(path, F_OK) != 0)
		exit(perror_no_file_dir(path));
	if (stat(path, &path_stat) < 0)
		exit(perror_no_file_dir(path));
	if ((path_stat.st_mode & S_IFMT) == S_IFDIR)
		exit(perror_is_dir(path));
	if (access(path, X_OK) != 0)
		exit(perror_no_permission(path));
}
