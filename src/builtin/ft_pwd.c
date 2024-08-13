/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongclee <dongclee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 18:09:29 by dongclee          #+#    #+#             */
/*   Updated: 2024/08/13 21:54:06 by dongclee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ms_error.h"

int	execute_pwd(void)
{
	char	*pwd;

	pwd = safe_malloc(sizeof(char) * 1000);
	if (!getcwd(pwd, 1000))
	{
		free(pwd);
		return (perror_cmd("pwd"));
	}
	ft_putendl_fd(pwd, 1);
	free(pwd);
	return (SUCCESS);
}
