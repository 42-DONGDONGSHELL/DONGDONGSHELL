/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_struct.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drhee <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 07:31:34 by drhee             #+#    #+#             */
/*   Updated: 2024/08/14 14:25:45 by drhee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_STRUCT_H
# define DATA_STRUCT_H

# include "minishell.h"

// data_struct.c
t_linkedlist	*create_linkedlist(void);
t_node			*create_node(void *content);
void			push(t_linkedlist *linkedlist, void *content);
void			*pop(t_linkedlist *linkedlist);
void			*popleft(t_linkedlist *linkedlist);

// data_struct_utils.c
char			*linkedlist_to_str(t_linkedlist *linkedlist);
void			free_linkedlist(t_linkedlist *linkedlist);

#endif
