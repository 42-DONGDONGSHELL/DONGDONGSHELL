#ifndef MS_ERROR_H
#define MS_ERROR_H

# include "minishell.h"

int	perror_cmd(char *cmd);
int	perror_arg(char *arg);
int	perror_cmd_arg(char *cmd, char *arg);
int	perror_cmd_arg_msg(char *cmd, char *arg, char *msg, int	exit_code);
int	perror_cmd_msg(char *cmd, char *msg, int	exit_code);

int	perror_identifier(char *cmd, char *arg);
int perror_numeric(char *cmd, char *arg);
int perror_many_arg(char *cmd);
int	perror_not_set(char *cmd, char *arg);
int	perror_is_dir(char *arg);
int	perror_no_file_dir(char *arg);
int	perror_cmd_not_found(char *cmd);
int	perror_no_permission(char *arg);
int	perror_etc(void);

#endif
