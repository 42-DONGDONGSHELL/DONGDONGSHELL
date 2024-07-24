/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drhee <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 14:53:44 by drhee             #+#    #+#             */
/*   Updated: 2024/07/24 20:15:10 by drhee            ###   ########.fr       */
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

// data_struct_free.c
void	free_linkedlist(t_linkedlist *linkedlist);

// parse.c
int	parse(char *line);

#endif
