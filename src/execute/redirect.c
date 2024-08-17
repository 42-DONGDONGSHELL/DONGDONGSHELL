/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongclee <dongclee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 16:25:08 by dongclee          #+#    #+#             */
/*   Updated: 2024/08/16 16:25:09 by dongclee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ms_execute.h"
#include "../../include/ms_error.h"

int	check_file(char *path)
{
	struct stat	path_stat;

	if (access(path, F_OK) != 0)
		return (perror_no_file_dir(path));
	if (stat(path, &path_stat) < 0)
		return (perror_etc());
	if ((path_stat.st_mode & S_IFMT) == S_IFDIR)
		return (perror_is_dir(path));
	if (access(path, X_OK) != 0)
		return (perror_no_permission(path));
	return (perror_etc());
}

int	redirect_readfile(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (check_file(path));
	else if (fd == 0)
		return (SUCCESS);
	if (dup2(fd, STDIN_FILENO) < 0)
	{
		close(fd);
		return (perror_cmd("dup2"));
	}
	close(fd);
	return (SUCCESS);
}

int	redirect_writefile(char *path, int need_reset)
{
	int	fd;

	if (need_reset)
		fd = open(path, O_CREAT | O_RDWR | O_TRUNC, 0644);
	else
		fd = open(path, O_CREAT | O_RDWR | O_APPEND, 0644);
	if (fd < 0)
		return (check_file(path));
	else if (fd == 0 || fd == 1)
		return (SUCCESS);
	if (dup2(fd, STDOUT_FILENO) < 0)
	{
		close(fd);
		return (perror_cmd("dup2"));
	}
	close(fd);
	return (SUCCESS);
}

int	handle_redirection(t_token *token, char *heredoc)
{
	t_node	*file;
	int		ret;

	ret = 0;
	file = (t_node *) token->file_head;
	while (file)
	{
		if (file->type == 4)
			ret = redirect_readfile(file->next->content);
		else if (file->type == 5)
			ret = redirect_readfile(heredoc);
		else if (file->type == 2)
			ret = redirect_writefile(file->next->content, 1);
		else if (file->type == 3)
			ret = redirect_writefile(file->next->content, 0);
		file = file->next->next;
	}
	return (ret);
}
