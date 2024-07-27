/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_envsubst.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drhee <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 21:07:16 by drhee             #+#    #+#             */
/*   Updated: 2024/07/28 04:42:04 by drhee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parse.h"

char	*ft_envsubst(char *line, t_envp *envp_dict)
{
	t_linkedlist	*line_list;		// 한글자씩 주소 저장
	t_linkedlist	*envp_key_list;	// 환경변수 key 한글자씩 주소 저장
	char			*envp_key;		// 환경변수 key str
	char			*envp_value;	// 환경변수 value str
	char			*envsubst_line;	//치환된 str
	int				i;
	int				j;

	i = 0;
	line_list = create_linkedlist();							// free
	while (line[i])
	{
		if (line[i] == '$')
		{
			envp_key_list = create_linkedlist();				// free
			i++;
			while (line[i] && (ft_isalnum(line[i]) || line[i] == '_'))
			{
				push(envp_key_list, &(line[i]));
				i++;
			}
			envp_key = linkedlist_to_str(envp_key_list);		// free
			free_linkedlist(envp_key_list);
			envp_value = find_envp_value(envp_dict, envp_key);
			if(!envp_value)
			{
				safe_free((void**) &envp_key);
				continue;
			}
			j = 0;
			while (envp_value[j])
			{
				push(line_list, &(envp_value[j]));
				j++;
			}
			safe_free((void**) &envp_key);
		}
		else
		{
			push(line_list, &(line[i]));
			i++;
		}
	}
	envsubst_line = linkedlist_to_str(line_list);
	free_linkedlist(line_list);
	return (envsubst_line);
}
