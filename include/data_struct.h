/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_struct.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drhee <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 07:31:34 by drhee             #+#    #+#             */
/*   Updated: 2024/08/16 17:56:07 by drhee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_STRUCT_H
# define DATA_STRUCT_H

# include "minishell.h"

t_linkedlist	*create_linkedlist(void);
t_node			*create_node(void *content);
void			push(t_linkedlist *linkedlist, void *content);
void			*pop(t_linkedlist *linkedlist);
void			*popleft(t_linkedlist *linkedlist);

char			*linkedlist_to_str(t_linkedlist *linkedlist);
void			free_linkedlist(t_linkedlist *linkedlist);

#endif
