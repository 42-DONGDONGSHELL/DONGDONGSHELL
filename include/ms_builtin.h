/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtin.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drhee <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 17:49:46 by drhee             #+#    #+#             */
/*   Updated: 2024/08/16 17:49:47 by drhee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_BUILTIN_H
# define MS_BUILTIN_H

# include "minishell.h"

int		ft_export(char *str, char ***envv);
char	*key_to_value_loc(char *key, char **envv);

int		execute_cd(t_token *token);
int		execute_echo(t_token *token);
int		execute_env(t_token *token);
int		execute_export(t_token *token);
int		execute_pwd(void);
int		execute_unset(t_token *token);
int		execute_exit(t_token *token);

int		is_declared(char *str);
void	print_all_env(char **env);

#endif
