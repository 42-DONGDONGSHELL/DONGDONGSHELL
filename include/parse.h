/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drhee <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 14:53:44 by drhee             #+#    #+#             */
/*   Updated: 2024/07/28 01:45:10 by drhee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "minishell.h"

// data_struct.c
t_linkedlist	*create_linkedlist(void);
t_node			*create_node(void *content);
void			push(t_linkedlist *linkedlist, void *content);
void			*pop(t_linkedlist *linkedlist);
char			*linkedlist_to_str(t_linkedlist *linkedlist);

// data_struct_free.c
void			free_linkedlist(t_linkedlist *linkedlist);

// envp.c
char			*find_envp_value(t_envp *envp_dict, char *key);
void			free_envp_dict(t_envp *envp_dict);
t_envp			*create_envp_dict(char **envp);

// ft_envsubst.c
char			*ft_envsubst(char *line, t_envp *envp_dict);

// parse.c
int				parse(char *line, char **envp);

#endif
