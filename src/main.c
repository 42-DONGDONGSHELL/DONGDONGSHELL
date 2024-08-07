/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drhee <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 18:56:04 by drhee             #+#    #+#             */
/*   Updated: 2024/08/07 22:50:28 by drhee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	g_exit_code = 0;

char	*set_home(char **envp)
{
	t_envp	*envp_dict;
	char	*home;

	envp_dict = create_envp_dict(envp);
	home = ft_strdup(find_envp_value(envp_dict, "HOME"));
	free_envp_dict(envp_dict);
	return (home);
}

int	main(int argc, char **argv, char **envp)
{
	t_linkedlist	*token_list;
	char			*line;
	char			*home;

	(void) argc;
	(void) argv;
	home = set_home(envp);
	while (1)
	{
		token_list = NULL;
		printf("tl %p\n", token_list);
		line = readline("minishell$ ");
		token_list = parse(line, token_list, envp, home);
		printf("tl after %p\n", token_list);
		if (token_list == NULL)
			continue;
		safe_free((void **) &line);
		free_token_list(token_list);
	}
	safe_free((void **) &home);
}
