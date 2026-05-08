/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_3d.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryatan <ryatan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 19:58:28 by ryatan            #+#    #+#             */
/*   Updated: 2026/05/08 09:32:21 by ryatan           ###   ########.fr       */
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
	map->rows = count_rows(outer_array);
	if (map->rows == 0)
		return (0);
	map->rows_array = ft_calloc(map->rows, sizeof(t_int_array));
	map->colors = ft_calloc(map->rows, sizeof(int *));
	if (!map->rows_array || !map->colors)
		return (free(map->rows_array), free(map->colors), 0);
	if (!fill_rows(outer_array, map))
		return (0);
	map->cols = (map->rows_array[0]).count;
	return (1);
}

int	split_rows(char *outer_array_row, t_int_array *z_array, int **colors_row)
{
	char		**split_array;
	int			n;

	split_array = ft_split(outer_array_row, ' ');
	if (!split_array)
		return (0);
	n = 0;
	while (split_array[n])
		n++;
	if (n == 0)
		return (free_all(split_array), 0);
	z_array->array = malloc(n * sizeof(int));
	*colors_row = malloc(n * sizeof(int));
	if (!z_array->array || !*colors_row)
		return (free(z_array->array), free(*colors_row), free_all(split_array),
			0);
	z_array->count = n;
	fill_arrays(split_array, n, z_array, colors_row);
	free_all(split_array);
	return (1);
}

void	compute_scale(t_map *map, t_win_data *w)
{
	int	map_w;
	int	map_h;

	if (map->rows == 0 || map->cols == 0)
		return ;
	map_w = (map->cols + map->rows);
	map_h = (map->cols + map->rows) / 2 + (map->z_max - map->z_min);
	if (map_h == 0)
		map_h = 1;
	map->scale = w->win_w / map_w;
	if (w->win_h / map_h < map->scale)
		map->scale = w->win_h / map_h;
	if (map->scale < 1)
		map->scale = 1;
	map->offset_x = w->win_w / 2;
	map->offset_y = (w->win_h - (map->rows + map->cols)
			* sin(0.523599) * map->scale) / 2
		+ (map->z_max - map->z_min) * map->scale / 2;
}

int	parse_color(char *token)
{
	char	*comma;

	comma = ft_strchr(token, ',');
	if (!comma)
		return (-1);
	return (hex_to_dec(comma + 1));
}
