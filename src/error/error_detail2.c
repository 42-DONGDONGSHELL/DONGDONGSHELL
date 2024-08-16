/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_detail2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongclee <dongclee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 16:02:08 by dongclee          #+#    #+#             */
/*   Updated: 2024/08/16 16:11:17 by dongclee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ms_error.h"

int	perror_is_dir(char *arg)
{
	return (perror_cmd_msg(arg, "is a directory", 126));
}

int	perror_no_file_dir(char *arg)
{
	return (perror_cmd_msg(arg, "No such file or directory", 1));
}

int	perror_cmd_not_found(char *cmd)
{
	return (perror_cmd_msg(cmd, "command not found", 127));
}

int	perror_no_permission(char *arg)
{
	return (perror_cmd_msg(arg, "Permission denied", 126));
}

int	perror_etc(void)
{
	ft_putstr_fd("ddsehll: ", 2);
	ft_putendl_fd("unexpected error", 2);
	return (ERROR);
}
