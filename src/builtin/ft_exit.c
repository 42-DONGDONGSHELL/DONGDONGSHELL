#include "../../include/builtin.h"

int	is_all_digit(char *str)
{
	int	i;
	
	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	execute_exit(t_token *token)
{
    int	status;

    ft_putendl_fd("exit", STDERR_FILENO);
    if (token->argv[2] != NULL)
    {
        ft_putendl_fd("ddshell: exit: too many arguments", STDERR_FILENO);
        return (ERROR);
    }
    if (!token->argv[1])
		status = 0;
	else if (is_all_digit(token->argv[1]))
		status = ft_atoi(token->argv[1]);
	else
	{
		ft_putstr_fd("ddshell: exit: ", STDERR_FILENO);
		ft_putstr_fd(token->argv[1], STDERR_FILENO);
		ft_putendl_fd(": numeric argument required", STDERR_FILENO);
		status = 255;
	}
	// todo : free 에 대한 고민
	exit(status);
}