/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_operator.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drhee <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 01:44:33 by drhee             #+#    #+#             */
/*   Updated: 2024/08/09 19:22:48 by drhee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parse.h"

int	is_operator(char c)
{
	if (c == '>' || c == '<' || c == '|')
		return (1);
	return (0);
}

char	*replace_operator(int operator)
{
	char	*operator_str;
	char	*result;
	int		size;

	if (operator == OUTPUT)
		operator_str = ">";
	else if (operator == APPEND_OUTPUT)
		operator_str = ">>";
	else if (operator == INPUT)
		operator_str = "<";
	else if (operator == HEREDOC)
		operator_str = "<<";
	else if (operator == PIPE)
		operator_str = "|";
	else
		return (NULL);
	size = ft_strlen(operator_str);
	result = (char *)safe_malloc(sizeof(char) * (size + 1));
	ft_strlcpy(result, operator_str, size + 1);
	return (result);
}

int	check_operators(char *c)
{
	if (*c == '>')
	{
		if (*(c + 1) == '>')
			return (APPEND_OUTPUT);
		return (OUTPUT);
	}
	else if (*c == '<')
	{
		if (*(c + 1) == '<')
			return (HEREDOC);
		return (INPUT);
	}
	else if (*(c) == '|')
		return (PIPE);
	return (0);
}

void	push_command(t_linkedlist *parsed_list, char *line, int start, int end)
{
	char	*command;

	command = ft_safe_substr(line, start, end - start);
	push(parsed_list, command);
}

t_linkedlist	*parse_operator(char *line)
{
	t_linkedlist	*parsed_list;
	char			*operator;
	int				i;
	int				start;

	start = 0;
	i = 0;
	parsed_list = create_linkedlist();
	while (line[i])
	{
		if (is_operator(line[i]) && is_in_quotes(line, &line[i]) == 0)
		{
			operator = replace_operator(check_operators(&line[i]));
			if (i > start)
				push_command(parsed_list, line, start, i);
			push(parsed_list, operator);
			parsed_list->tail->type = check_operators(&line[i]);
			i += ft_strlen(operator) - 1;
			start = i + 1;
		}
		i++;
	}
	push_command(parsed_list, line, start, i);
	return (parsed_list);
}

