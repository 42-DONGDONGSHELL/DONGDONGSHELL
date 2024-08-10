#include "../../include/minishell.h"

void	print_more_info(char *info1, char *info2)
{
	if (info1)
	{
		ft_putstr_fd(info1, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	if (info2)
	{
		ft_putstr_fd(info2, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
}

int	print_error(int exit_code, int err_no, char *info1, char *info2)
{
	ft_putstr_fd("ddshell: ", STDERR_FILENO);
	print_more_info(info1, info2);
	if (err_no == 1)
		ft_putendl_fd("no such file or directory", STDERR_FILENO);
	return (exit_code);
}
