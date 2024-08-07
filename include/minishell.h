/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drhee <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 18:36:25 by drhee             #+#    #+#             */
/*   Updated: 2024/08/07 21:30:50 by drhee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"

# include <stdio.h>				// printf, perror
# include <stdlib.h>			// malloc, free, exit, getenv
# include <unistd.h>			// read, write, access, open, close, fork, execve, dup, dup2, pipe, getcwd, chdir, isatty, ttyname, ttyslot, tcsetattr, tcgetattr
# include <sys/types.h>			// wait, waitpid, wait3, wait4, opendir, readdir, closedir, stat, lstat, fstat
# include <sys/wait.h>			// wait, waitpid, wait3, wait4
# include <sys/stat.h>			// stat, lstat, fstat
# include <fcntl.h>				// open, unlink
# include <dirent.h>			// opendir, readdir, closedir
# include <string.h>			// strerror
# include <errno.h>				// errno
# include <signal.h>			// signal, sigaction, sigemptyset, sigaddset, kill
# include <termios.h>			// tcsetattr, tcgetattr
# include <termcap.h>			// tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs
# include <readline/readline.h>	// readline, rl_clear_history, rl_on_new_line, rl_replace_line, rl_redisplay
# include <readline/history.h>	// add_history

# include "data.h"
# include "data_struct.h"
# include "parse.h"

extern int	g_exit_code;

# define FALSE 0
# define TRUE 1
# define ERROR 1
# define SUCCESS 0

enum	e_token
{
	ETC = 0,
	PIPE = 1,
	OUTPUT = 2,
	APPEND_OUTPUT = 3,
	INPUT = 4,
	HEREDOC = 5,
	REDIRECT = 6,
};

void	safe_free(void **ptr);
void	*safe_malloc(size_t size);
int		is_whitespace(char c);
int		is_str_whitespace(char *str);
void 			free_token_list(t_linkedlist *token_list);

#endif
