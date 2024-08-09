/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongclee <dongclee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 08:04:30 by drhee             #+#    #+#             */
/*   Updated: 2024/08/04 16:52:54 by dongclee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parse.h"

int	parse(char *line)
{
	t_linkedlist	*linkedlist;

	linkedlist = create_linkedlist();
	push(linkedlist, line);
	printf("head: %s\n", (char *)linkedlist->head->content);
	pop(linkedlist);
	free(linkedlist);
	return (0);
}
