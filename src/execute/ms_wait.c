/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_wait.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongclee <dongclee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 16:17:51 by dongclee          #+#    #+#             */
/*   Updated: 2024/08/16 16:17:58 by dongclee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ms_w_int(int w)
{
	return (*(int *)&(w));
}

int	ms_wstatus(int x)
{
	return (ms_w_int(x) & 0177);
}

int	ms_wifexited(int x)
{
	return (ms_wstatus(x) == 0);
}

int	ms_wexitstatus(int x)
{
	return (((x) & 0xff00) >> 8);
}

int	status_to_exit_code(int status)
{
	int	exit_code;

	if (ms_wifexited(status))
		exit_code = ms_wexitstatus(status);
	else
		exit_code = ms_wstatus(status) + 128;
	return (exit_code);
}
