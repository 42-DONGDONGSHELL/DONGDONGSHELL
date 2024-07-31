/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drhee <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 08:04:30 by drhee             #+#    #+#             */
/*   Updated: 2024/07/31 14:28:05 by drhee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parse.h"

int	parse(char *line, char **envp)
{
	char	*envsubst_line;
	t_envp	*envp_dict;

	envp_dict = create_envp_dict(envp);
	envsubst_line = envsubst(line, envp_dict);
	if (!envsubst_line)
	{
		free_envp_dict(envp_dict);
		return (1);
	}
	printf("%s\n", envsubst_line);
	free_envp_dict(envp_dict);
	safe_free((void **) &envsubst_line);
	return (0);
}
