/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_detail.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongclee <dongclee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 16:00:54 by dongclee          #+#    #+#             */
/*   Updated: 2024/08/16 16:03:25 by dongclee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ms_error.h"

int	perror_identifier(char *cmd, char *arg)
{
	return (perror_cmd_arg_msg(cmd, arg, "not a valid identifier", 1));
}

int	perror_numeric(char *cmd, char *arg)
{
	return (perror_cmd_arg_msg(cmd, arg, "numeric argument required", 255));
}

int	perror_many_arg(char *cmd)
{
	return (perror_cmd_msg(cmd, "too many arguments", 1));
}

int	perror_not_set(char *cmd, char *arg)
{
	ft_putstr_fd("ddsehll: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(" ", 2);
	ft_putendl_fd("not set", 2);
	return (ERROR);
}
