/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drhee <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 08:04:30 by drhee             #+#    #+#             */
/*   Updated: 2024/07/24 20:14:34 by drhee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parse.h"

int	parse(char *line)
{
	t_linkedlist	*linkedlist;

	linkedlist = create_linkedlist();
	push(linkedlist, line);
	printf("head: %s\n", linkedlist->head->content);
	pop(linkedlist);
	free(linkedlist);
	return (0);
}
