/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongclee <dongclee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 16:37:59 by dongclee          #+#    #+#             */
/*   Updated: 2024/08/08 16:33:24 by dongclee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/execute.h"

/**
 * 자식 프로세스가 실행하는 함수
 */
void	child(t_token *token, int fd[2], int fd_in, char *heredoc)
{
	if (token->list_info->size == token->list_info->token_cnt - 1)
	{
		if (dup2(fd_in, STDIN_FILENO) < 0)
			// todo : error 처리
		close(fd_in);
	}
	close(fd[0]);
	if (token->list_info->size == 0)
		if (dup2(fd[1], STDOUT_FILENO) < 0)
			// todo : error 처리
	close(fd[1]);
	start_cmd(token, heredoc);
}

/**
 * 자식 프로세스 생성
 */
void	make_child(t_token *token, int fd[2], int fd_in, char *heredoc)
{
	static int	i;

	token->list_info->pid[i] = fork();
	if (token->list_info->pid[i] < 0)
		// todo : error
	if (token->list_info->pid[i] == 0)
		child(token, fd, fd_in, heredoc);
	i++;
}

void	wait_child(t_linkedlist *list)
{
	int	i;
	int	status;

	i = 0;
	g_exit = 0;
	while (i < list->token_cnt)
	{
		waitpid(list->pid[i], &status, 0);
		i++;
	}
	if (WIFEXITED(status))
		g_exit = WEXITSTATUS(status);
}

int	execute(t_linkedlist *list)
{
	int	fd[2];
	int	fd_in;
	char	*last_heredoc;
	t_token	*token;

	fd_in = 0;
	while (list->size != 0)
	{
		token = (t_token *) pop(list);
		if (list->size != 0)
			pipe(fd);
		last_heredoc = read_heredoc(token);
		make_child(token, fd, fd_in, last_heredoc);
		close(fd[1]);
		if (fd_in != 0)
			close(fd_in);
		if (last_heredoc == NULL) // 만약 히어독이 없다면 fd[0] (파이프 읽기)를 fd_in으로
			fd_in = fd[0];
		else // 만약 히어독이 있다면 fd[0] (파이프 읽기)를 닫고, 히어독 파일을 fd_in으로
		{
			close(fd[0]);
			fd_in = open(last_heredoc, O_RDONLY);
		}
	}
	wait_child(list);
	return (SUCCESS);
}
