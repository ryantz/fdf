/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryatan <ryatan@student.42singapore.sg      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 13:27:05 by ryatan            #+#    #+#             */
/*   Updated: 2025/12/11 17:44:05 by ryatan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(char *str)
{
	int	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	len;
	size_t	i;
	size_t	j;
	char	*p_strjoin;

	len = ft_strlen(s1) + ft_strlen(s2);
	p_strjoin = malloc(sizeof(char) * len + 1);
	if (!p_strjoin)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[j])
		p_strjoin[i++] = s1[j++];
	j = 0;
	while (s2[j])
		p_strjoin[i++] = s2[j++];
	p_strjoin[i] = '\0';
	return (p_strjoin);
}

char	*ft_strchr(char *s, int c)
{
	unsigned char	d_c;

	d_c = (unsigned char)c;
	while (*s)
	{
		if (*s == d_c)
			return ((char *)s);
		s++;
	}
	if (d_c == '\0')
		return ((char *)s);
	return (NULL);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*c_dest;
	unsigned char	*c_src;
	size_t			i;

	c_dest = (unsigned char *)dest;
	c_src = (unsigned char *)src;
	i = 0;
	while (i < n)
	{
		c_dest[i] = c_src[i];
		i++;
	}
	return (dest);
}

char	*ft_strdup(char *s)
{
	char	*dup;
	size_t	i;
	size_t	len;

	len = ft_strlen(s);
	dup = malloc(sizeof(char) * len + 1);
	if (!dup)
		return (NULL);
	i = 0;
	while (i < len)
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (&dup[0]);
}
