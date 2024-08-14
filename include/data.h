/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drhee <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 21:42:52 by drhee             #+#    #+#             */
/*   Updated: 2024/08/14 15:18:49 by drhee            ###   ########.fr       */
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
	int				type;
}	t_node;

typedef struct s_linkedlist
{
	t_node			*head;
	t_node			*tail;
	int				size;
	int				*pid;
	int				token_cnt;
}	t_linkedlist;

typedef struct s_envp
{
	char			*key;
	char			*value;
}	t_envp;

typedef struct s_token
{
	char			*cmd;
	char			**argv;
	int				argc;
	char			***envp;
	t_node			*file_head;
	t_linkedlist	*file_list;
	t_linkedlist	*list_info;
}	t_token;

typedef struct s_env
{
	char			*home;
	int				exit_code;
	t_envp			*envp_dict;
}	t_env;

typedef struct s_quote
{
	int				s_quote;
	int				d_quote;
}	t_quote;

#endif
