/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongclee <dongclee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 16:37:59 by dongclee          #+#    #+#             */
/*   Updated: 2024/08/16 14:53:32 by dongclee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ms_execute.h"
#include "../../include/ms_signal.h"
#include "../../include/ms_error.h"
#include "../../include/ms_wait.h"

/**
 * 자식 프로세스가 실행하는 함수
 */
void	child(t_token *token, int fd[2], int fd_in, char *heredoc)
{
	if ((t_token *) token->list_info->head->content != token)
	{
		if (dup2(fd_in, STDIN_FILENO) < 0)
			perror_cmd("dup2");
		if (fd_in != STDIN_FILENO)
			close(fd_in);
	}
	close(fd[0]);
	if ((t_token *) token->list_info->tail->content != token)
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

	if ((t_token *) token->list_info->head->content != token)
		i = 0;
	token->list_info->pid[i] = fork();
	if (token->list_info->pid[i] < 0)
		perror_cmd("fork");
	if (token->list_info->pid[i] == 0)
	{
		child(token, fd, fd_in, heredoc);
	}
	ft_signal_ignore();
	i++;
}

int	wait_child(t_linkedlist *list)
{
	int	i;
	int	status;

	i = 0;
	while (i < list->token_cnt)
	{
		waitpid(list->pid[i], &status, 0);
		i++;
	}
	ft_signal_prompt();
	return (status_to_exit_code(status));
}

void init_pid_array(t_linkedlist *token_list)
{
	if (token_list->pid != NULL)
	{
		free(token_list->pid);
		token_list->pid = NULL;
	}
	token_list->pid = (pid_t *)malloc(sizeof(int) * token_list->token_cnt);
	if (token_list->pid == NULL)
		perror_cmd("malloc");
	memset(token_list->pid, 0, sizeof(int) * token_list->token_cnt);
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
	t_node	*node;

	fd_in = 0;
	init_pid_array(list);
	node = list->head;
	while (node != NULL)
	{
		token = (t_token *) node->content;
		if (node->next != NULL)
			pipe(fd);
		last_heredoc = read_heredoc(token);
		make_child(token, fd, fd_in, last_heredoc);
		close(fd[1]);
		if (fd_in != STDIN_FILENO)
			close(fd_in);
		if (last_heredoc == NULL) // 만약 히어독이 없다면 fd[0] (파이프 읽기)를 fd_in으로
			fd_in = fd[0];
		else // 만약 히어독이 있다면 fd[0] (파이프 읽기)를 닫고, 히어독 파일을 fd_in으로
		{
			close(fd[0]);
			fd_in = open(last_heredoc, O_RDONLY);
		}
		node = node->next;
	}
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
	if (tp == 2 || tp == 5 || tp == 7 || (tp == 4 && token->argv[1] != NULL))
	{
		exit_code = do_builtin(token, tp);
		return (exit_code);
	}
	last_heredoc = read_heredoc(token);
	pid = fork();
	if (pid < 0)
		perror_cmd("fork");
	if (pid == 0)
		start_cmd(token, last_heredoc);
	ft_signal_ignore();
	waitpid(pid, &status, 0);
	exit_code = status_to_exit_code(status);
	if (last_heredoc != NULL)
		free(last_heredoc);
	ft_signal_prompt();
	return (exit_code);
}
