#ifndef MS_SIGNAL_H
# define MS_SIGNAL_H

# include "minishell.h"

void	set_terminal_print_off(void);
void	set_terminal_print_on(void);

void	sigint_heredoc_handler(int signum);
void	sigint_prompt_handler(int signum);
void	sigterm_prompt_handler();

void	ft_signal_heredoc(void);
void	ft_signal_prompt(void);
void	ft_signal_ignore(void);
void	ft_signal_default(void);

#endif