/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryatan <ryatan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 20:00:59 by ryatan            #+#    #+#             */
/*   Updated: 2026/05/08 10:02:02 by ryatan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	hex_to_dec(char *str)
{
	int		result;
	int		i;
	char	c;

	result = 0;
	i = 0;
	if (str[0] == '0' && (str[1] == 'x' || str[1] == 'X'))
		i = 2;
	while (str[i])
	{
		c = ft_tolower(str[i]);
		if (c >= '0' && c <= '9')
			result = result * 16 + (c - '0');
		else if (c >= 'a' && c <= 'f')
			result = result * 16 + (c - 'a' + 10);
		i++;
	}
	return (result);
}

void	free_all(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	free_map(t_map *map)
{
	int	i;

	i = 0;
	while (i < map->rows)
	{
		if (map->rows_array && map->rows_array[i].array)
			free(map->rows_array[i].array);
		if (map->colors && map->colors[i])
			free(map->colors[i]);
		i++;
	}
	free(map->rows_array);
	free(map->colors);
}

int	count_rows(char **outer_array)
{
	int	rows;

	rows = 0;
	while (outer_array[rows])
		rows++;
	return (rows);
}

int	fill_rows(char **outer_array, t_map *map)
{
	int	i;

	i = 0;
	while (i < map->rows)
	{
		if (!split_rows(outer_array[i], &(map->rows_array)[i],
			&(map->colors)[i]))
			return (map->rows = i, free_map(map), 0);
		if (i > 0 && map->rows_array[i].count != map->rows_array[0].count)
			return (map->rows = i + 1, free_map(map), 0);
		i++;
	}
	return (1);
}
