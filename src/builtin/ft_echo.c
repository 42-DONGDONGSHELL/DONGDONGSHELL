/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongclee <dongclee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 16:13:45 by dongclee          #+#    #+#             */
/*   Updated: 2024/07/24 16:13:46 by dongclee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	has_option(char **argv, int *p_idx)
{
	int	op;
	int	j;

	op = 0;
	*p_idx = 1;
	while (argv[*p_idx])
	{
		if (argv[*p_idx][0] == '-' && argv[*p_idx][1] == 'n')
		{
			j = 2;
			while (argv[*p_idx][j] == 'n')
				j++;
			if (argv[*p_idx][j] == '\0')
				op = 1;
			else
				break ;
		}
		else
			break ;
		(*p_idx)++;
	}
	return (op);
}

int	ft_echo(t_token *token)
{
	int	idx;
	int	option;

	option = has_option(token->argv, &idx);
	while (token->argv[idx])
	{
		ft_putstr_fd(token->argv[idx], 1);
		if (token->argv[idx + 1])
			ft_putchar_fd(' ', 1);
		idx++;
	}
	if (!option)
		write(1, "\n", 1);
	return (SUCCESS);
}
