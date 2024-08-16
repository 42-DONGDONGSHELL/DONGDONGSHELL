/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drhee <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 14:53:44 by drhee             #+#    #+#             */
/*   Updated: 2024/08/16 17:55:06 by drhee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "minishell.h"

char			*find_envp_value(t_envp *envp_dict, char *key);
void			free_envp_dict(t_envp *envp_dict);
t_envp			*create_envp_dict(char **envp, int exit_code);

char			*envsubst(char *line, t_env *env_data);
char			*envsubst_heredoc(char *line, t_envp *envp_dict);

void			free_token_list(t_linkedlist *token_list);

int				are_quotes_balanced(const char *str);
int				consecutive_operator_check(t_linkedlist *trimmed_list);
void			print_parse_error(int error_code);

int				is_operator(char c);
t_linkedlist	*parse_operator(char *line);

int				parse(char *line, t_linkedlist **tk, char ***envp, t_env *env);

int				is_in_quotes(const char *str, const char *target_addr);

char			*strip_quotes(char *str);
void			replace_quotes(t_linkedlist *token_list);

t_linkedlist	*create_token_list(t_linkedlist *envsubst_list, char ***envp);

char			*trim_whitespace(const char *str);
t_linkedlist	*trim_list(t_linkedlist *parsed_list);

#endif
