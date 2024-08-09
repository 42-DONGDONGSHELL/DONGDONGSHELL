/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strip_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drhee <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 20:10:01 by drhee             #+#    #+#             */
/*   Updated: 2024/08/09 21:04:37 by drhee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parse.h"

char	*strip_quotes(char *str)
{
	t_linkedlist	*str_list;
	t_linkedlist	*quote_list;
	char			*quote_str;
	char			*new_str;
	int 			i;
	char 			*c;


	i = 0;
	str_list = create_linkedlist();
	while (str[i])
	{
		printf("%d\n", is_in_quotes(str, &str[i]));
		printf("i: %d\n", i);
		if (str[i] == '\'' && is_in_quotes(str, &str[i]) == 1)
		{
			quote_list = create_linkedlist();
			i++;
			while (str[i] && str[i] != '\'')
				push(quote_list, &str[i++]);
			quote_str = linkedlist_to_str(quote_list);
			while (*quote_str)
				push(str_list, quote_str++);
			free_linkedlist(quote_list);
		}
		else if (str[i] == '\"' && is_in_quotes(str, &str[i]) == 2)
		{
			quote_list = create_linkedlist();
			i++;
			while (str[i] && str[i] != '\"')
				push(quote_list, &str[i++]);
			quote_str = linkedlist_to_str(quote_list);
			while (*quote_str)
				push(str_list, quote_str++);
			free_linkedlist(quote_list);
		}
		else
		{
			c = malloc(sizeof(char *) * 2);
			*c = str[i];
			*(c + 1) = '\0';
			push(str_list, c);
		}
		i++;
	}
	new_str = linkedlist_to_str(str_list);
	t_node *node = str_list->head;

	free_linkedlist(str_list);
	return (new_str);
}

void check_leak()
{
	system("leaks a.out");
}

int main()
{
	atexit(check_leak);
	char *str = "hello \"wor\'ld\" \'gd\' world";
	char *new_str = strip_quotes(str);
	printf("%s\n", new_str);
	free(new_str);

	return (0);
}
