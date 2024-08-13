/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongclee <dongclee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 18:56:04 by drhee             #+#    #+#             */
/*   Updated: 2024/08/13 22:00:21 by dongclee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/ms_execute.h"

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
	int				parse_result;

	(void) argc;
	(void) argv;
	home = set_home(envp);
	envp_copy = ft_envpdup(envp);
	while (1)
	{
		token_list = NULL;
		line = readline("minishell$ ");
		if (!line)
			break ;
		if (ft_strncmp(line, "", 1) == 0)
			continue ;
		parse_result = parse(line, &token_list, &envp_copy, home);
		safe_free((void **) &line);
		if (parse_result)
		{
			print_parse_error(parse_result);
			continue ;
		}
		if (token_list->token_cnt == 1)
		{
			execute_single((t_token *) token_list->head->content);
		}
		envp_copy = *((t_token *) token_list->head->content)->envp;
		print_token(token_list);
		free_token_list(token_list);
	}
	free_envp(envp_copy);
	safe_free((void **) &home);
}
