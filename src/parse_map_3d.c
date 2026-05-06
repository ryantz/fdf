/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_3d.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryatan <ryatan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 19:58:28 by ryatan            #+#    #+#             */
/*   Updated: 2026/05/06 20:00:37 by ryatan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		split_rows(char *outer_array_row, t_int_array *z_array,
			int **colors_row);
int		parse_color(char *token);

void	print_map_3d(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->rows)
	{
		j = 0;
		while (j < map->cols)
		{
			ft_printf("%d ,", map->rows_array[i].array[j]);
			j++;
		}
		ft_printf("\n");
		i++;
	}
}

int	parse_map_3d(char **outer_array, t_map *map)

{
	int	i;

	i = 0;
	map->rows = 0;
	while (outer_array[map->rows])
		map->rows++;
	map->rows_array = malloc(map->rows * sizeof(t_int_array));
	map->colors = malloc(map->rows * sizeof(int *));
	while (i < map->rows)
	{
		split_rows(outer_array[i], &(map->rows_array)[i], &(map->colors)[i]);
		i++;
	}
	map->cols = (map->rows_array[0]).count;
	return (1);
}

int	split_rows(char *outer_array_row, t_int_array *z_array, int **colors_row)
{
	char		**split_array;
	int			split_array_elements;
	int			i;

	split_array = ft_split(outer_array_row, ' ');
	split_array_elements = 0;
	while (split_array[split_array_elements])
		split_array_elements++;
	z_array->array = malloc(split_array_elements * sizeof(int));
	*colors_row = malloc(split_array_elements * sizeof(int));
	z_array->count = split_array_elements;
	i = 0;
	while (i < split_array_elements)
	{
		(z_array->array)[i] = ft_atoi(split_array[i]);
		(*colors_row)[i] = parse_color(split_array[i]);
		i++;
	}
	free_all(split_array);
	return (1);
}

void	compute_scale(t_map *map, t_win_data *w)
{
	int	map_w;
	int	map_h;

	map_w = (map->cols + map->rows);
	map_h = (map->cols + map->rows) / 2 + map->z_max;
	map->scale = w->win_w / map_w;
	if (w->win_h / map_h < map->scale)
		map->scale = w->win_h / map_h;
	if (map->scale < 1)
		map->scale = 1;
	map->offset_x = w->win_w / 2;
	map->offset_y = (w->win_h - (map->rows + map->cols)
			* sin(0.523599) * map->scale) / 2
		+ map->z_max * map->scale / 2;
}

int	parse_color(char *token)
{
	char	*comma;

	comma = ft_strchr(token, ',');
	if (!comma)
		return (-1);
	return (hex_to_dec(comma + 1));
}
