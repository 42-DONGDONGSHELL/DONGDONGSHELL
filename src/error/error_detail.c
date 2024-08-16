#include "../../include/ms_error.h"

/**
 * export 시 ?=value와 같이 key가 이상한 경우.
 * unset 시 key가 이상한 경우.
 * @param cmd
 * @param arg
 * @return
 */
int	perror_identifier(char *cmd, char *arg)
{
	return (perror_cmd_arg_msg(cmd, arg, "not a valid identifier", 1));
}

int perror_numeric(char *cmd, char *arg)
{
	return(perror_cmd_arg_msg(cmd, arg, "numeric argument required", 255));
}

int perror_many_arg(char *cmd)
{
	return (perror_cmd_msg(cmd, "too many arguments", 1));
}

/**
 * 파싱부에서 NULL이 온 경우.
 * @param cmd
 * @param arg
 * @return
 */
int	perror_syntax(char *cmd, char *arg)
{
	return(perror_cmd_arg_msg(cmd, "syntax error near unexpected token", arg, 258));
}

int	perror_not_set(char *cmd, char *arg)
{
	ft_putstr_fd("ddsehll: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(" ", 2);
	ft_putendl_fd("not set", 2);
	return (ERROR);
}

int	perror_is_dir(char *arg)
{
	return (perror_cmd_msg(arg, "is a directory", 126));
}

int	perror_no_file_dir(char *arg)
{
	return (perror_cmd_msg(arg, "No such file or directory", 1));
}

int	perror_cmd_not_found(char *cmd)
{
	return (perror_cmd_msg(cmd, "command not found", 127));
}

int	perror_no_permission(char *arg)
{
	return (perror_cmd_msg(arg, "Permission denied", 126));
}

int	perror_etc()
{
	ft_putstr_fd("ddsehll: ", 2);
	ft_putendl_fd("unexpected error", 2);
	return (ERROR);
}
