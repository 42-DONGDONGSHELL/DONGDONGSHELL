/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongclee <dongclee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 18:36:25 by drhee             #+#    #+#             */
/*   Updated: 2024/08/16 16:36:52 by drhee            ###   ########.fr       */
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

extern int	g_sigint;

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
	NLINE = 6,
	QUOTES = 7,
};

// utils.c
void	safe_free(void **ptr);
void	*safe_malloc(size_t size);
int		is_whitespace(char c);
int		is_str_whitespace(char *str);
int		array_size(char **arr);

// ft_utils.c
char	*ft_safe_strdup(const char *s1);
char	*ft_safe_substr(char const *s, unsigned int start, size_t len);
char	**ft_envpdup(char **envp);
void	free_envp(char **envp_copy);

#endif
