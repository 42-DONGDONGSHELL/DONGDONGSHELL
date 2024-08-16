/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drhee <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 18:56:04 by drhee             #+#    #+#             */
/*   Updated: 2024/08/16 16:37:53 by drhee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/ms_execute.h"
#include "../include/ms_signal.h"

int	g_sigint = 0;

void	sigterm_prompt_handler(void)
{
	ft_putstr_fd("\033[1A", STDERR_FILENO);
	ft_putstr_fd("\033[12C", STDERR_FILENO);
	ft_putstr_fd("exit\n", STDERR_FILENO);
}

char	*set_home(char **envp)
{
	t_envp	*envp_dict;
	char	*home;

	envp_dict = create_envp_dict(envp, 0);
	home = ft_safe_strdup(find_envp_value(envp_dict, "HOME"));
	free_envp_dict(envp_dict);
	return (home);
}

void	init_env(t_env *env, char **envp)
{
	env->home = set_home(envp);
	env->exit_code = 0;
	env->envp_dict = NULL;
}

#include "../include/ms_wait.h"
int	main(int argc, char **argv, char **envp)
{
	t_linkedlist	*token_list;
	char			*line;
	char			**envp_copy;
	int				parse_result;
	t_env			env;

	(void) argc;
	(void) argv;
	init_env(&env, envp);
	envp_copy = ft_envpdup(envp);
	ft_signal_prompt();
	while (1)
	{
		token_list = NULL;
		line = readline("minishell$ ");
		if (g_sigint)
			env.exit_code = 1;
		if (!line)
		{
			sigterm_prompt_handler();
			break ;
		}
		if (ft_strncmp(line, "", 1) == 0)
		{
			safe_free((void **) &line);
			continue ;
		}
		add_history(line);
		parse_result = parse(line, &token_list, &envp_copy, &env);
		safe_free((void **) &line);
		if (parse_result)
		{
			print_parse_error(parse_result);
			env.exit_code = 258;
			continue ;
		}
		g_sigint = 0;
		if (token_list->token_cnt == 1)
			env.exit_code = execute_single((t_token *) token_list->head->content);
		else
			env.exit_code = execute(token_list);
		envp_copy = *((t_token *) token_list->head->content)->envp;
//		print_token(token_list);
		free_token_list(token_list);
	}
	free_envp(envp_copy);
	safe_free((void **) &(env.home));
}
