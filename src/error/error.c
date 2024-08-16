/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongclee <dongclee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 16:11:06 by dongclee          #+#    #+#             */
/*   Updated: 2024/08/16 16:11:07 by dongclee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	perror_cmd(char *cmd)
{
	char	*err_msg;

	err_msg = strerror(errno);
	ft_putstr_fd("ddsehll: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(err_msg, 2);
	errno = 0;
	return (1);
}

int	perror_arg(char *arg)
{
	char	*err_msg;

	err_msg = strerror(errno);
	ft_putstr_fd("ddsehll: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(err_msg, 2);
	errno = 0;
	return (1);
}

int	perror_cmd_arg(char *cmd, char *arg)
{
	char	*err_msg;

	err_msg = strerror(errno);
	ft_putstr_fd("ddsehll: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(err_msg, 2);
	errno = 0;
	return (1);
}

int	perror_cmd_arg_msg(char *cmd, char *arg, char *msg, int exit_code)
{
	ft_putstr_fd("ddsehll: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(msg, 2);
	return (exit_code);
}

int	perror_cmd_msg(char *cmd, char *msg, int exit_code)
{
	ft_putstr_fd("ddsehll: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(msg, 2);
	return (exit_code);
}
