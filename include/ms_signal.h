/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_signal.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drhee <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 17:52:09 by drhee             #+#    #+#             */
/*   Updated: 2024/08/16 18:23:19 by drhee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_SIGNAL_H
# define MS_SIGNAL_H

# include "minishell.h"

void	set_terminal_print_off(void);
void	set_terminal_print_on(void);

void	sigint_heredoc_handler(int signum);
void	sigint_prompt_handler(int signum);

void	ft_signal_heredoc(void);
void	ft_signal_prompt(void);
void	ft_signal_ignore(void);
void	ft_signal_default(void);

#endif
