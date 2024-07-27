/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongclee <dongclee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 16:13:48 by dongclee          #+#    #+#             */
/*   Updated: 2024/07/24 16:13:49 by dongclee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_env(char **envv)
{
	int i;

	i = 0;
	while (envv[i])
	{
		ft_putendl_fd(envv[i], 1);
		i++;
	}
	return (SUCCESS);
}
