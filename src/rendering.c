/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryatan <ryatan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/26 22:17:18 by ryatan            #+#    #+#             */
/*   Updated: 2026/04/27 21:43:54 by ryatan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	draw_point(t_win_data *w_data, t_point *point, int y_coord_gap);
int	render_x(char *array_row, t_win_data *w_data, t_point *point,
		int y_coord_gap);
int	draw_y_line(t_win_data *w_data, t_point *point, int y_coord_gap);
int	draw_x_line(t_win_data *w_data, t_point *point, int x_coord_gap);

int	render_2d_grid(char **outer_array)
{
	t_win_data	w_data;
	t_point		point;
	int			i;
	int			outer_array_len;
	int			y_coord_gap;

	i = 0;
	point.x = 10;
	point.y = 10;
	outer_array_len = 0;
	w_data = init_win_data();
	while (outer_array[outer_array_len])
		outer_array_len++;
	y_coord_gap = 680 / (outer_array_len - 1);
	while (i < outer_array_len)
	{
		render_x(outer_array[i], &w_data, &point, y_coord_gap);
		point.y += y_coord_gap;
		ft_printf("point.y: %d\n", point.y);
		point.x = 10;
		i++;
	}
	window_loop(&w_data);
	return (1);
}

int	render_x(char *array_row, t_win_data *w_data, t_point *point,
		int y_coord_gap)
{
	char	**split_array;
	int		split_array_len;
	int		x_coord_gap;
	int		i;

	split_array_len = 0;
	split_array = ft_split(array_row, ' ');
	while (split_array[split_array_len])
		split_array_len++;
	ft_printf("array_len: %d\n", split_array_len);
	x_coord_gap = 680 / (split_array_len - 1);
	i = 0;
	while (i < split_array_len)
	{
		draw_point(w_data, point, y_coord_gap);
		ft_printf("point %d drawn\n", i + 1);
		draw_x_line(w_data, point, x_coord_gap);
		point->x += x_coord_gap;
		i++;
	}
	return (1);
}

int	draw_y_line(t_win_data *w_data, t_point *point, int y_coord_gap)
{
	int	start;
	int	end;

	start = point->y + 1;
	end = point->y + (y_coord_gap - 1);
	while (start <= end && end < 700)
	{
		mlx_pixel_put(w_data->mlx, w_data->win, point->x, start, WHITE);
		start++;
	}
	return (1);
}

int	draw_x_line(t_win_data *w_data, t_point *point, int x_coord_gap)
{
	int	start;
	int	end;

	start = point->x + 1;
	end = point->x + (x_coord_gap - 1);
	while (start <= end && end < 700)
	{
		mlx_pixel_put(w_data->mlx, w_data->win, start, point->y, WHITE);
		start++;
	}
	return (1);
}

int	draw_point(t_win_data *w_data, t_point *point, int y_coord_gap)
{
	mlx_pixel_put(w_data->mlx, w_data->win, point->x, point->y, RED);
	draw_y_line(w_data, point, y_coord_gap);
	return (1);
}
