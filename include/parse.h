/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drhee <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 14:53:44 by drhee             #+#    #+#             */
/*   Updated: 2024/08/01 21:23:41 by drhee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "minishell.h"

// envp.c
char			*find_envp_value(t_envp *envp_dict, char *key);
void			free_envp_dict(t_envp *envp_dict);
t_envp			*create_envp_dict(char **envp);

// envsubst.c
char			*envsubst_heredoc(char *line, t_envp *envp_dict);
char			*envsubst(char *line, t_env_h *env_data);

// parse.c
int				parse(char *line, char **envp, char *home);

int				is_in_quotes(const char *str, const char *target_addr);

// parse_operator.c
int				is_operator(char c);
t_linkedlist	*parse_operator(char *line);

#endif
