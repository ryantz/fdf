/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryatan <ryatan@student.42singapore.sg      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 20:52:55 by ryatan            #+#    #+#             */
/*   Updated: 2026/01/21 11:18:30 by ryatan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_read_line(int fd, char **storage);
int		ft_append_storage(char *data, char **storage);
char	*ft_scan_storage(char match, char **storage);
int		ft_remove_from_storage(char match, char **storage);

char	*get_next_line(int fd)
{
	static char	*storage;
	char		*return_string;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	return_string = ft_scan_storage('\n', &storage);
	if (return_string)
		return (return_string);
	return (ft_read_line(fd, &storage));
}

char	*ft_read_line(int fd, char **storage)
{
	ssize_t	bytes_read;
	char	*buffer;
	char	*return_string;

	buffer = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	while (1)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read <= 0)
			break ;
		buffer[bytes_read] = '\0';
		ft_append_storage(buffer, storage);
		return_string = ft_scan_storage('\n', storage);
		if (return_string)
			return (free(buffer), return_string);
	}
	free(buffer);
	if (bytes_read < 0 || !*storage || !**storage)
		return (free(*storage), *storage = NULL, NULL);
	return_string = ft_strdup(*storage);
	return (free(*storage), *storage = NULL, return_string);
}

int	ft_append_storage(char *data, char **storage)
{
	size_t	data_len;
	char	*new_storage;

	if (!data || data[0] == '\0')
		return (0);
	data_len = ft_strlen(data);
	if (!*storage)
	{
		*storage = malloc(sizeof(char) * data_len + 1);
		if (!*storage)
			return (0);
		ft_memcpy(*storage, data, data_len);
		(*storage)[data_len] = '\0';
		return (1);
	}
	else
	{
		new_storage = ft_strjoin(*storage, data);
		if (!new_storage)
			return (0);
		free(*storage);
		*storage = new_storage;
		return (1);
	}
}

char	*ft_scan_storage(char match, char **storage)
{
	int		end;
	char	*found;

	if (!*storage)
		return (NULL);
	end = 0;
	while ((*storage)[end])
	{
		if ((*storage)[end] == match)
		{
			end += 1;
			break ;
		}
		end++;
	}
	if (!ft_strchr(*storage, match))
		return (NULL);
	found = malloc(sizeof(char) * (end + 1));
	if (!found)
		return (NULL);
	ft_memcpy(found, *storage, end);
	found[end] = '\0';
	ft_remove_from_storage(match, storage);
	return (found);
}

int	ft_remove_from_storage(char match, char **storage)
{
	char	*ptr_remainder;
	size_t	len_ptr_remainder;
	char	*remainder;

	ptr_remainder = ft_strchr(*storage, match);
	if (!ptr_remainder)
		return (0);
	ptr_remainder++;
	len_ptr_remainder = ft_strlen(ptr_remainder);
	remainder = malloc(sizeof(char) * (len_ptr_remainder + 1));
	if (!remainder)
		return (0);
	ft_memcpy(remainder, ptr_remainder, len_ptr_remainder);
	remainder[len_ptr_remainder] = '\0';
	free(*storage);
	*storage = remainder;
	return (1);
}
