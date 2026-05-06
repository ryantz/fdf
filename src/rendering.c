/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryatan <ryatan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/26 22:17:18 by ryatan            #+#    #+#             */
/*   Updated: 2026/05/06 20:27:31 by ryatan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	put_pixel(t_win_data *w_data, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= w_data->win_w || y < 0 || y >= w_data->win_h)
		return ;
	dst = w_data->addr + (y * w_data->line_len + x * (w_data->bpp / 8));
	*(unsigned int *)dst = color;
}

t_point	project(int x, int y, int z, t_map *map)
{
	t_point	p;

	p.x = (int)((x - y) * cos(0.523599) * map->scale) + map->offset_x;
	p.y = (int)((x + y) * sin(0.523599) * map->scale
			- z * map->scale) + map->offset_y;
	return (p);
}

void	bresenham(t_win_data *w, t_point p0, t_point p1, int color)
{
	t_bres	b;
	int		sx;
	int		sy;

	b.dx = abs(p1.x - p0.x);
	b.dy = -abs(p1.y - p0.y);
	sx = (p0.x < p1.x) * 2 - 1;
	sy = (p0.y < p1.y) * 2 - 1;
	b.err = b.dx + b.dy;
	while (!(p0.x == p1.x && p0.y == p1.y))
	{
		put_pixel(w, p0.x, p0.y, color);
		b.e2 = 2 * b.err;
		if (b.e2 >= b.dy)
		{
			b.err += b.dy;
			p0.x += sx;
		}
		if (b.e2 <= b.dx)
		{
			b.err += b.dx;
			p0.y += sy;
		}
	}
	put_pixel(w, p0.x, p0.y, color);
}

void	draw_connections(t_win_data *w, t_map *map, int i, int j)
{
	t_point	cur;
	int		color;

	cur = project(j, i, map->rows_array[i].array[j], map);
	color = WHITE;
	if (map->colors[i][j] != -1)
		color = map->colors[i][j];
	if (j + 1 < map->cols)
		bresenham(w, cur,
			project(j + 1, i, map->rows_array[i].array[j + 1], map),
			color);
	if (i + 1 < map->rows)
		bresenham(w, cur,
			project(j, i + 1, map->rows_array[i + 1].array[j], map),
			color);
}

void	render_iso(t_win_data *w, t_map *map)
{
	int		i;
	int		j;

	i = 0;
	while (i < map->rows)
	{
		j = 0;
		while (j < map->cols)
			draw_connections(w, map, i, j++);
		i++;
	}
	mlx_put_image_to_window(w->mlx, w->win, w->img, 0, 0);
}
