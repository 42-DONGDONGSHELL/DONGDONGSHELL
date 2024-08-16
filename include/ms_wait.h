/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_wait.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drhee <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 17:52:52 by drhee             #+#    #+#             */
/*   Updated: 2024/08/16 17:53:05 by drhee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_WAIT_H
# define MS_WAIT_H

# include "minishell.h"

int	ms_w_int(int w);
int	ms_wstatus(int x);
int	ms_wifexited(int x);
int	ms_wexitstatus(int x);
int	status_to_exit_code(int status);

#endif
