/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drhee <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 18:56:04 by drhee             #+#    #+#             */
/*   Updated: 2024/07/18 01:33:11 by drhee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


int		main(int argc, char *argv[], char ** envp)
{
	char *line;

	(void) argc;
	(void) argv;
	while (1)
	{
		line = readline("minishell$ ");
		parse(line);
		free(line);
	}
}
