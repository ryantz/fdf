/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryatan <ryatan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/26 22:17:18 by ryatan            #+#    #+#             */
/*   Updated: 2026/05/01 14:34:38 by ryatan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	put_pixel(t_win_data *w_data, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= 700 || y < 0 || y >= 700)
		return ;
	dst = w_data->addr + (y * w_data->line_len + x * (w_data->bpp / 8));
	*(unsigned int *)dst = color;
}

t_point	project(int x, int y, int z)
{
	t_point	p;

	p.x = (int)((x - y) * cos(0.523599) * ISO_SCALE) + OFFSET_X;
	p.y = (int)((x + y) * sin(0.524599) * ISO_SCALE - z * ISO_SCALE)
		+ OFFSET_Y;
	return (p);
}

void    bresenham(t_win_data *w, t_point p0, t_point p1, int color)
{
    int    dx;
    int    dy;
    int    sx;
    int    sy;
    int    err;
    int    e2;

    dx = abs(p1.x - p0.x);
    dy = -abs(p1.y - p0.y);
    sx = p0.x < p1.x ? 1 : -1;   // step direction x
    sy = p0.y < p1.y ? 1 : -1;   // step direction y
    err = dx + dy;
    while (1)
    {
        put_pixel(w, p0.x, p0.y, color);
        if (p0.x == p1.x && p0.y == p1.y)
            break ;
        e2 = 2 * err;
        if (e2 >= dy) { err += dy; p0.x += sx; }
        if (e2 <= dx) { err += dx; p0.y += sy; }
    }
}

void    render_iso(t_win_data *w, t_map *map)
{
    int        i;
    int        j;
    t_point    cur;
    t_point    next;

    i = 0;
    while (i < map->rows)
    {
        j = 0;
        while (j < map->cols)
        {
            cur = project(j, i, map->rows_array[i].array[j]);

            // draw line to the right neighbour
            if (j + 1 < map->cols)
            {
                next = project(j + 1, i, map->rows_array[i].array[j + 1]);
                bresenham(w, cur, next, WHITE);
            }
            // draw line to the bottom neighbour
            if (i + 1 < map->rows)
            {
                next = project(j, i + 1, map->rows_array[i + 1].array[j]);
                bresenham(w, cur, next, WHITE);
            }
            j++;
        }
        i++;
    }
    mlx_put_image_to_window(w->mlx, w->win, w->img, 0, 0);
}
