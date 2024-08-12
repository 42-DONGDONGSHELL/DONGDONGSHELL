/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drhee <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 18:56:04 by drhee             #+#    #+#             */
/*   Updated: 2024/08/12 10:49:54 by drhee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	g_exit_code = 0;

char	*set_home(char **envp)
{
	t_envp	*envp_dict;
	char	*home;

	envp_dict = create_envp_dict(envp);
	home = ft_safe_strdup(find_envp_value(envp_dict, "HOME"));
	free_envp_dict(envp_dict);
	return (home);
}

int	main(int argc, char **argv, char **envp)
{
	t_linkedlist	*token_list;
	char			*line;
	char			*home;
	char			**envp_copy;

	(void) argc;
	(void) argv;
	home = set_home(envp);
	envp_copy = ft_envpdup(envp);
	while (1)
	{
		token_list = NULL;
		line = readline("minishell$ ");
		if(!line)
			break ;
		token_list = parse(line, token_list, envp_copy, home);
		safe_free((void **) &line);
		if (token_list == NULL)
			continue ;
		print_token(token_list);
		free_token_list(token_list);
	}
	free_envp(envp_copy);
	safe_free((void **) &home);
}
