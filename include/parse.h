/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drhee <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 14:53:44 by drhee             #+#    #+#             */
/*   Updated: 2024/08/09 17:27:29 by drhee            ###   ########.fr       */
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

int				is_in_quotes(const char *str, const char *target_addr);

// parse_operator.c
int				is_operator(char c);
t_linkedlist	*parse_operator(char *line);

// parse.c
t_linkedlist	*parse(char *line, t_linkedlist *token_list,char **envp, char *home);

// token.c
t_linkedlist	*create_token_list(t_linkedlist *envsubst_list, char **envp);

int				are_quotes_balanced(const char *str);

void 			print_token(t_linkedlist *token_list);

#endif
