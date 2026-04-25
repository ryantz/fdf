#include "fdf.h"

// pos_x pos_y is the starting points

int	draw_line(t_win_data *w_data, t_point *point, int len, char orientation);
int	generate_from_array(char *array_row, t_win_data *w_data);

int render_loop(char *array_row)
{
	t_win_data	w_data;

	w_data = init_win_data();
	generate_from_array(array_row, &w_data);
	window_loop(&w_data);
	return (1);
}

int	generate_from_array(char *array_row, t_win_data *w_data)
{
	char	**split_array;
	int		split_array_len;
	int		draw_line_len;
	int		i;
	t_point	point;

	point.x = 0;
	point.y = 10;
	split_array_len = 0;
	split_array = ft_split(array_row, ' ');
	while (split_array[split_array_len])
		split_array_len++;
	draw_line_len = 700 / (split_array_len - 1);
	i = 0;
	while (i < split_array_len)
	{
		draw_line(w_data, &point, draw_line_len, 'h');
		point.x += draw_line_len;
		i++;
	}
	return (1);
}

int	draw_line(t_win_data *w_data, t_point *point, int len, char orientation)
{
	int	i;

	i = 0;
	if (orientation == 'h')
	{
		while (i <= len)
		{
			mlx_pixel_put(w_data->mlx, w_data->win, point->x, point->y, WHITE);
			point->x++;
			i++;
		}
	}
	else if (orientation == 'v')
	{
		while (i <= len)
		{
			mlx_pixel_put(w_data->mlx, w_data->win, point->x, point->y, WHITE);
			point->y++;
			i++;
		}
	}
	else
		return (0);
	return (1);
}

//int	render_line(t_win_data *w_data, t_point *point)
//{
//	int			val;
//	int			i;
//	char		*array1[5] = {"0", NULL};
//	//char		array2 = {"0", "0", "0", "0", NULL}
//
//	i = 0;
//	while (array1[i])
//	{
//		val = ft_atoi(array1[i]);
//		if (val == 0)
//			draw_line(w_data, point, 'h');
//		i++;
//	}
//	return (1);
//}
