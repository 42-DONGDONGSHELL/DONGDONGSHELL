/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongclee <dongclee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 17:05:17 by dongclee          #+#    #+#             */
/*   Updated: 2024/08/16 17:13:20 by dongclee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	handle_fd_in(int fd[2], char *last_heredoc)
{
	int	fd_in;

	if (last_heredoc == NULL)
		fd_in = fd[0];
	else
	{
		close(fd[0]);
		fd_in = open(last_heredoc, O_RDONLY);
	}
	return (fd_in);
}

void	init_pid_array(t_linkedlist *token_list)
{
	if (token_list->pid != NULL)
	{
		free(token_list->pid);
		token_list->pid = NULL;
	}
	token_list->pid = (pid_t *)safe_malloc(sizeof(int) * token_list->token_cnt);
	memset(token_list->pid, 0, sizeof(int) * token_list->token_cnt);
}
