/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongclee <dongclee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 16:09:20 by dongclee          #+#    #+#             */
/*   Updated: 2024/08/16 16:17:39 by dongclee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ms_execute.h"

/**
 * 빌드인 함수인지 확인 후 맞는 인덱스 반환
 */
int	is_builtin(t_token *token)
{
	int	len;

	if (token->cmd == NULL)
		return (-1);
	len = ft_strlen(token->cmd) + 1;
	if (ft_strncmp(token->cmd, "echo", len) == 0)
		return (1);
	else if (ft_strncmp(token->cmd, "cd", len) == 0)
		return (2);
	else if (ft_strncmp(token->cmd, "pwd", len) == 0)
		return (3);
	else if (ft_strncmp(token->cmd, "export", len) == 0)
		return (4);
	else if (ft_strncmp(token->cmd, "unset", len) == 0)
		return (5);
	else if (ft_strncmp(token->cmd, "env", len) == 0)
		return (6);
	else if (ft_strncmp(token->cmd, "exit", len) == 0)
		return (7);
	else
		return (-1);
}

/**
 * 빌트인 함수 실행
 */
int	do_builtin(t_token *token, int builtin_idx)
{
	int	ret;

	ret = SUCCESS;
	if (builtin_idx == 1)
		ret = execute_echo(token);
	else if (builtin_idx == 2)
		ret = execute_cd(token);
	else if (builtin_idx == 3)
		ret = execute_pwd();
	else if (builtin_idx == 4)
		ret = execute_export(token);
	else if (builtin_idx == 5)
		ret = execute_unset(token);
	else if (builtin_idx == 6)
		ret = execute_env(token);
	else if (builtin_idx == 7)
		ret = execute_exit(token);
	return (ret);
}
