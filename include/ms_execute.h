/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_execute.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drhee <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 17:51:36 by drhee             #+#    #+#             */
/*   Updated: 2024/08/16 17:51:57 by drhee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_EXECUTE_H
# define MS_EXECUTE_H

# include "minishell.h"
# include "ms_builtin.h"

void	child(t_token *token, int fd[2], int fd_in, char *heredoc);
void	make_child(t_token *token, int fd[2], int fd_in, char *heredoc);
int		execute(t_linkedlist *list);

char	*create_heredoc_filepath(t_token *token);
char	*read_heredoc(t_token *token);
int		redirect_readfile(char *path);
int		redirect_writefile(char *path, int need_reset);
int		handle_redirection(t_token *token, char *heredoc);

int		is_builtin(t_token *token);
int		do_builtin(t_token *token, int builtin_idx);

char	**get_bin_paths(char **envp);
void	free_arr(char **arr);
char	*find_executable_path(char *cmd, char **envp);
int		search_cmd(t_token *token);
void	start_cmd(t_token *token, char *heredoc);
int		execute_single(t_token *token);

int		handle_fd_in(int fd[2], char *last_heredoc);
void	init_pid_array(t_linkedlist *token_list);

#endif
