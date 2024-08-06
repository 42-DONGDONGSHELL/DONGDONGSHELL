/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drhee <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 18:56:04 by drhee             #+#    #+#             */
/*   Updated: 2024/08/01 22:28:52 by drhee            ###   ########.fr       */
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
	char	*line;
	char	*home;

	(void) argc;
	(void) argv;
	home = set_home(envp);
	while (1)
	{
		line = readline("minishell$ ");
		parse(line, envp, home);
		safe_free((void **) &line);
	}
	safe_free((void **) &home);
}
