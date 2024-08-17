/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drhee <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 18:36:25 by drhee             #+#    #+#             */
/*   Updated: 2024/08/16 17:57:35 by drhee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <dirent.h>
# include <string.h>
# include <errno.h>
# include <signal.h>
# include <termios.h>
# include <termcap.h>
# include <readline/readline.h>
# include <readline/history.h>

# include "data.h"
# include "data_struct.h"
# include "parse.h"
# include "ms_execute.h"
# include "ms_signal.h"
# include "ms_wait.h"

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

void	safe_free(void **ptr);
void	*safe_malloc(size_t size);
int		is_whitespace(char c);
int		is_str_whitespace(char *str);
int		array_size(char **arr);

char	*ft_safe_strdup(const char *s1);
char	*ft_safe_substr(char const *s, unsigned int start, size_t len);
char	**ft_envpdup(char **envp);
void	free_envp(char **envp_copy);

#endif
