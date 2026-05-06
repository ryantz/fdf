/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_event.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryatan <ryatan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 20:00:51 by ryatan            #+#    #+#             */
/*   Updated: 2026/05/06 20:47:20 by ryatan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	find_z_range(t_map *map, int *z_min, int *z_max)
{
	int	i;
	int	j;
	int	z;

	*z_min = map->rows_array[0].array[0];
	*z_max = map->rows_array[0].array[0];
	i = 0;
	while (i < map->rows)
	{
		j = 0;
		while (j < map->rows_array[i].count)
		{
			z = map->rows_array[i].array[j];
			if (z < *z_min)
				*z_min = z;
			if (z > *z_max)
				*z_max = z;
			j++;
		}
		i++;
	}
}

t_win_data	init_win_data(void)
{
	t_win_data	w_data;

	w_data.win_w = 1280;
	w_data.win_h = 900;
	w_data.mlx = mlx_init();
	w_data.win = mlx_new_window(w_data.mlx, w_data.win_w,
			w_data.win_h, "ryatan's fdf");
	w_data.img = mlx_new_image(w_data.mlx, w_data.win_w, w_data.win_h);
	w_data.addr = mlx_get_data_addr(w_data.img, &w_data.bpp, &w_data.line_len,
			&w_data.endian);
	return (w_data);
}

int	window_close_handler(t_fdf *fdf)
{
	free_map(fdf->map);
	mlx_destroy_image(fdf->w->mlx, fdf->w->img);
	mlx_destroy_window(fdf->w->mlx, fdf->w->win);
	mlx_destroy_display(fdf->w->mlx);
	free(fdf->w->mlx);
	exit(0);
	return (1);
}

void	window_loop(t_win_data *w_data, t_fdf *fdf)
{
	mlx_hook(w_data->win, 17, 0, window_close_handler, fdf);
	mlx_loop(w_data->mlx);
}
