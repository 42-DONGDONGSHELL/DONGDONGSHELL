/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongclee <dongclee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 16:13:04 by dongclee          #+#    #+#             */
/*   Updated: 2024/08/16 16:13:25 by dongclee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ms_signal.h"

void	sigint_heredoc_handler(int signum)
{
	(void)signum;
	ft_putstr_fd("\n", STDERR_FILENO);
	exit (1);
}

void	sigint_prompt_handler(int signum)
{
	(void)signum;
	ft_putstr_fd("\n", STDERR_FILENO);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_sigint = 1;
}
