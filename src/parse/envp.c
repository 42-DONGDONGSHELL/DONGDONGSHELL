/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drhee <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 16:16:03 by drhee             #+#    #+#             */
/*   Updated: 2024/08/12 12:02:06 by drhee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parse.h"

char	*find_envp_value(t_envp *envp_dict, char *key)
{
	int	i;
	int	size_a;
	int	size_b;
	int	size;

	i = 0;
	size_a = ft_strlen(key);
	while (envp_dict[i].key)
	{
		size_b = ft_strlen(envp_dict[i].key);
		if (size_a > size_b)
			size = size_a;
		else
			size = size_b;
		if (!ft_strncmp(envp_dict[i].key, key, size))
			return (envp_dict[i].value);
		i++;
	}
	return (NULL);
}

void	free_envp_dict(t_envp *envp_dict)
{
	int	i;

	i = 0;
	while (envp_dict[i].key)
	{
		safe_free((void **) &envp_dict[i].key);
		safe_free((void **) &envp_dict[i].value);
		i++;
	}
	safe_free((void **) &envp_dict);
}

char	**split_envp(char *str)
{
	char	**s2 ;
	char	*delimiter;
	int		key_len;
	int		value_len;

	s2 = malloc(2 * sizeof(char *));
	delimiter = ft_strchr(str, '=');
	if (delimiter == NULL)
	{
		s2[0] = NULL;
		s2[1] = NULL;
		return (NULL);
	}
	key_len = delimiter - str;
	value_len = ft_strlen(delimiter + 1);
	s2[0] = safe_malloc((key_len + 1) * sizeof(char));
	s2[1] = safe_malloc((value_len + 1) * sizeof(char));
	ft_strlcpy(s2[0], str, key_len + 1);
	s2[0][key_len] = '\0';
	ft_strlcpy(s2[1], delimiter + 1, value_len + 1);
	s2[1][value_len] = '\0';
	return (s2);
}

t_envp	*create_envp_dict(char **envp)
{
	t_envp	*envp_dict;
	char	**splited_envp;
	int		i;

	i = 0;
	while (envp[i])
		i++;
	envp_dict = (t_envp *)safe_malloc(sizeof(t_envp) * (i + 2));
	i = 0;
	envp_dict[i].key = ft_safe_strdup("?");
	envp_dict[i].value = ft_itoa(g_exit_code);
	while (envp[i])
	{
		splited_envp = split_envp(envp[i]);
		envp_dict[i + 1].key = splited_envp[0];
		envp_dict[i + 1].value = splited_envp[1];
		safe_free((void **) &splited_envp);
		i++;
	}
	envp_dict[i + 1].key = NULL;
	envp_dict[i + 1].value = NULL;
	return (envp_dict);
}
