#include "../../include/ms_signal.h"

void	sigint_heredoc_handler(int signum)
{
	(void)signum;
	ft_putstr_fd("\n", STDERR_FILENO);
	exit (1);
}

void	sigint_prompt_handler(int signum)
{
	(void)signum;
	ft_putstr_fd("\n", STDERR_FILENO);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_sigint = 1;
}
