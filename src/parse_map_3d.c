#include "fdf.h"

/*
 * {
 * 	{0 10 0 0 0 0},
 * 	{0 0 0 0 0 0},
 * }
 */
int	split_rows(char *outer_array_row, t_int_array *z_array);

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
	while (i < map->rows)
	{
		split_rows(outer_array[i], &(map->rows_array)[i]);
		i++;
	}
	map->cols = (map->rows_array[0]).count;
	return (1);
}

int	split_rows(char *outer_array_row, t_int_array *z_array)
{
	char		**split_array;
	int			split_array_elements;
	int			i;

	split_array = ft_split(outer_array_row, ' ');
	split_array_elements = 0;
	while (split_array[split_array_elements])
		split_array_elements++;
	z_array->array = malloc(split_array_elements * sizeof(int));
	z_array->count = split_array_elements;
	i = 0;
	while (i < split_array_elements)
	{
		(z_array->array)[i] = ft_atoi(split_array[i]);
		i++;
	}
	free_all(split_array);
	return (1);
}
