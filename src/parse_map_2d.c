/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_2d.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryatan <ryatan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 11:38:09 by ryatan            #+#    #+#             */
/*   Updated: 2026/05/01 14:07:59 by ryatan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_outer_array	*init_outer(t_outer_array *outer);
t_outer_array	*create_array(char *map_file_path, t_outer_array *outer);
char			**process_map(char *map_file_path, t_outer_array *outer);

void	print_parsed_map(char **map, t_outer_array *outer)
{
	int	i;

	i = 0;
	while (i < outer->line_count)
	{
		ft_printf("line %d: %s\n", i + 1, map[i]);
		i++;
	}
}

char	**parse_map_2d(char *map_file_path, t_outer_array *outer)
{
	char	**array;

	init_outer(outer);
	create_array(map_file_path, outer);
	array = process_map(map_file_path, outer);
	print_parsed_map(array, outer);
	return (array);
}

// calloc used here for 2d array
char	**process_map(char *map_file_path, t_outer_array *outer)
{
	int		fd;
	int		line_len;
	int		i;
	char	*line;

	fd = open(map_file_path, O_RDONLY);
	if (fd < 0)
		return (NULL);
	i = 0;
	while (i < outer->line_count)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		else
		{
			line_len = ft_strlen(line) - 1;
			(outer->outer_array)[i] = ft_calloc(line_len + 1, sizeof(char));
			ft_memcpy((outer->outer_array)[i], line, line_len);
			free(line);
		}
		i++;
	}
	close(fd);
	return (outer->outer_array);
}

t_outer_array	*create_array(char *map_file_path, t_outer_array *outer)
{
	char			*line;
	int				fd;

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
			outer->line_count++;
			free(line);
		}
	}
	close(fd);
	outer->outer_array = malloc((outer->line_count + 1) * sizeof(char *));
	outer->outer_array[outer->line_count] = NULL;
	return (outer);
}

t_outer_array	*init_outer(t_outer_array *outer)
{
	outer->line_count = 0;
	outer->outer_array = NULL;
	return (outer);
}
