/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongclee <dongclee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 16:37:59 by dongclee          #+#    #+#             */
/*   Updated: 2024/08/13 21:58:03 by dongclee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ms_execute.h"
#include "../../include/ms_signal.h"
#include "../../include/ms_error.h"

/**
 * 자식 프로세스가 실행하는 함수
 */
void	child(t_token *token, int fd[2], int fd_in, char *heredoc)
{
	if (token->list_info->size == token->list_info->token_cnt - 1)
	{
		if (dup2(fd_in, STDIN_FILENO) < 0)
			perror_cmd("dup2");
		close(fd_in);
	}
	close(fd[0]);
	if (token->list_info->size == 0)
		if (dup2(fd[1], STDOUT_FILENO) < 0)
			perror_cmd("dup2");
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
		perror_cmd("dup2");
	if (token->list_info->pid[i] == 0)
	{
		ft_signal_default();
		child(token, fd, fd_in, heredoc);
	}
	ft_signal_ignore();
	i++;
}

int	wait_child(t_linkedlist *list)
{
	int	i;
	int	status;
	int	exit_code;

	i = 0;
	exit_code = 0;
	while (i < list->token_cnt)
	{
		waitpid(list->pid[i], &status, 0);
		i++;
	}
	if (WIFEXITED(status))
		exit_code = WEXITSTATUS(status);
	ft_signal_prompt();
	return (exit_code);
}

/**
 * 파이프가 있을 때 사용.
 * @param list
 * @return
 */
int	execute(t_linkedlist *list)
{
	int	fd[2];
	int	fd_in;
	char	*last_heredoc;
	t_token	*token;

	fd_in = 0;
	printf("execute :: start\n");
	while (list->size != 0)
	{
		printf("execute :: while loop start\n");
		token = (t_token *) pop(list);
		printf("execute :: token cmd=%s\n", token->cmd);
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
	printf("execute :: end\n");
	return (wait_child(list));
}

/**
 * 파이프가 없을 때 사용. ls | -> segmentfault 안니게
 * @param list
 */
int	execute_single(t_token *token)
{
	int	pid;
	int	status;
	int	tp;
	int	exit_code;
	char *last_heredoc;

	tp = is_builtin(token);
	exit_code = 0;
	if (tp == 2 || tp == 5 || tp == 7 || (tp == 4 && token->argv[1] != NULL))
	{
		exit_code = do_builtin(token, tp);
		return (exit_code);
	}
	last_heredoc = read_heredoc(token);
	pid = fork();
	if (pid < 0)
		perror_cmd("dup2");
	if (pid == 0)
		start_cmd(token, last_heredoc);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		exit_code = WEXITSTATUS(status);
	if (last_heredoc != NULL)
		free(last_heredoc);
	return (exit_code);
}
