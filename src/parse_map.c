/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryatan <ryatan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 11:38:09 by ryatan            #+#    #+#             */
/*   Updated: 2026/04/22 11:55:03 by ryatan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	count_lines_in_map(char *map_file_path)
{
	char	*line;
	int		line_count;
	int		fd;

	line_count = 0;
	fd = open(map_file_path, O_RDONLY);
	if (fd < 0)
		return (0);
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		else
		{
			line_count++;
			free(line);
		}
	}
	close(fd);
	return (line_count);
}

char	**parse_map(char *map_file_path, int line_count, char ***map_2d_array)
{
	int		fd;
	int		line_len;
	int		i;
	char	*line;

	fd = open(map_file_path, O_RDONLY);
	if (fd < 0)
		return (NULL);
	i = 0;
	while (i < line_count)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		else
		{
			line_len = ft_strlen(line) - 1;
			(*map_2d_array)[i] = ft_calloc(line_len + 1, sizeof(char));
			ft_memcpy((*map_2d_array)[i], line, line_len);
			free(line);
		}
		i++;
	}
	close(fd);
	return (*map_2d_array);
}
