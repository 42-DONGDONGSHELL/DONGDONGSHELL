/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drhee <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 21:37:04 by drhee             #+#    #+#             */
/*   Updated: 2024/06/05 14:15:47 by drhee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*new;
	size_t	slen;
	size_t	substr_len;

	if (!s)
		return (0);
	slen = ft_strlen(s);
	if (start >= slen)
		return (ft_strdup(""));
	substr_len = slen - start;
	if (substr_len > len)
		substr_len = len;
	new = (char *)malloc(sizeof(char) * (substr_len + 1));
	if (!new)
		return (0);
	ft_strlcpy(new, s + start, substr_len + 1);
	return (new);
}
