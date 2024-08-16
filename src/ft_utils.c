/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongclee <dongclee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 19:17:11 by drhee             #+#    #+#             */
/*   Updated: 2024/08/16 17:05:09 by dongclee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_safe_strdup(const char *s1)
{
	char	*str;

	str = ft_strdup(s1);
	if (str == NULL)
		exit(EXIT_FAILURE);
	return (str);
}

char	*ft_safe_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;

	str = ft_substr(s, start, len);
	if (str == NULL)
		exit(EXIT_FAILURE);
	return (str);
}

char	**ft_envpdup(char **envp)
{
	size_t	i;
	size_t	env_count;
	char	**envp_copy;

	env_count = 0;
	while (envp[env_count] != NULL)
		env_count++;
	envp_copy = (char **)safe_malloc((env_count + 1) * sizeof(char *));
	if (envp_copy == NULL)
		return (NULL);
	i = 0;
	while (i < env_count)
	{
		envp_copy[i] = ft_safe_strdup(envp[i]);
		i++;
	}
	envp_copy[env_count] = NULL;
	return (envp_copy);
}

void	free_envp(char **envp_copy)
{
	size_t	i;

	if (envp_copy == NULL)
		return ;
	i = 0;
	while (envp_copy[i] != NULL)
	{
		safe_free((void **)&envp_copy[i]);
		i++;
	}
	safe_free((void **)&envp_copy);
}
