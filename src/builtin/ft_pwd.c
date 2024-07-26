/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongclee <dongclee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 18:09:29 by dongclee          #+#    #+#             */
/*   Updated: 2024/07/24 18:09:31 by dongclee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_pwd(void)
{
	char	*pwd;

	if (!(pwd = malloc(sizeof(char) * 1000)))
		return (ERROR);
	if (!getcwd(pwd, sizeof(pwd)))
	{
		free(pwd);
		return (ERROR);
	}
	ft_putendl_fd(pwd, 1);
	free(pwd);
	return (SUCCESS);
}
