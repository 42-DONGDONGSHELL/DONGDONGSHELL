#include "../../include/ms_execute.h"

/**
 * "<" 나 "<<" 와 같이 input redirection일 경우 사용.
 * "<<" 인 경우 미리 생성된 heredoc경로를 집어넣을 것.
 */
int	redirect_readfile(char *path)
{
	int	fd;

	if ((fd = open(path, O_RDONLY)) < 0)
		return (ERROR); // todo : error handling
	else if (fd == 0)
		return (SUCCESS);
	if (dup2(fd, STDIN_FILENO) < 0)
	{
		close(fd);
		return (ERROR); // todo : error handling
	}
	close(fd);
	return (SUCCESS);
}

/**
 * ">" 나 ">>"와 같이 output redirection일 경우 사용
 * ">" 일 경우 reset이 필요하므로 1을 need_reset에 집어넣음
 * ">>" 일 경우 뒤에 이어붙이기 가능하므로 0를 need_reset에 집어넣음.
 */
int	redirect_writefile(char *path, int need_reset)
{
	int	fd;

	if (need_reset)
		fd = open(path, O_CREAT | O_RDWR | O_TRUNC, 0644);
	else
		fd = open(path, O_CREAT | O_RDWR | O_APPEND, 0644);
	if (fd < 0)
		return (ERROR); // todo : ERROR handling
	else if (fd == 0 || fd == 1)
		return (SUCCESS);
	if (dup2(fd, STDOUT_FILENO) < 0)
	{
		close(fd);
		return (ERROR); // todo : ERROR handling
	}
	close(fd);
	return (SUCCESS);
}

/**
 * t_node 배열을 순회하며 리다이랙션 처리.
 */
int	handle_redirection(t_token *token, char *heredoc)
{
	t_node	*file;
	int		ret;

	ret = 0;
	file = (t_node *) token->file_head;
	while (file)
	{
		if (file->type == 4) // 1 : "<"
			ret = redirect_readfile(file->next->content);
		else if (file->type == 5) // 2 : "<<"
			ret = redirect_readfile(heredoc);
		else if (file->type == 2) // 3 : ">"
			ret = redirect_writefile(file->next->content, 1);
		else if (file->type == 3) // 4 : ">>"
			ret = redirect_writefile(file->next->content, 0);
		file = file->next->next;
	}
	return (ret);
}
