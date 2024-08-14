#include "../../include/ms_builtin.h"
#include "../../include/ms_error.h"

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

	if (token->list_info->token_cnt == 1)
		ft_putendl_fd("exit", STDERR_FILENO);
	if (token->argc > 2)
		return (perror_many_arg("exit"));
	if (!token->argv[1])
		status = 0;
	else if (is_all_digit(token->argv[1]))
	{
		status = ft_atoi(token->argv[1]);
		status %= 256;
	}
	else
		status = perror_numeric("exit", token->argv[1]);
	// todo : free에 대한 고민.
	exit(status);
}