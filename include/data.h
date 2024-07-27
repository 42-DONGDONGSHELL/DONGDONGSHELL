/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drhee <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 21:42:52 by drhee             #+#    #+#             */
/*   Updated: 2024/07/27 22:33:52 by drhee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_H
# define DATA_H

# include "minishell.h"

typedef struct s_node
{
	void			*content;
	struct s_node	*prev;
	struct s_node	*next;
}	t_node;

typedef struct s_envp
{
	char			*key;
	char			*value;
}	t_envp;

typedef struct s_linkedlist
{
	t_node			*head;
	t_node			*tail;
	int				size;
}	t_linkedlist;

typedef struct s_token
{
	char			*cmd;
	char			**argv;
	char			**envp;
	struct t_node	*file_list;
}	t_token;

#endif
