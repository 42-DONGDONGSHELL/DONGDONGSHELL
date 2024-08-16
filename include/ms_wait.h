#ifndef MS_WAIT_H
#define MS_WAIT_H

# include "minishell.h"

int	ms_w_int(int w);
int	ms_wstatus(int x);
int	ms_wifexited(int x);
int	ms_wexitstatus(int x);
int	status_to_exit_code(int status);

#endif
