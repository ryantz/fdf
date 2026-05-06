/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryatan <ryatan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 09:27:16 by ryatan            #+#    #+#             */
/*   Updated: 2026/05/06 20:46:17 by ryatan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(int argc, char **argv)
{
	t_outer_array	outer;
	t_map			map;
	t_win_data		w_data;
	t_fdf			fdf;

	if (argc < 2)
		return (1);
	parse_map_2d(argv[1], &outer);
	parse_map_3d(outer.outer_array, &map);
	free_all(outer.outer_array);
	ft_printf("peak z = %d, color = %d\n", map.rows_array[20].array[13],
		map.colors[20][13]);
	w_data = init_win_data();
	find_z_range(&map, &(map.z_min), &(map.z_max));
	compute_scale(&map, &w_data);
	ft_printf("z_min=%d z_max=%d\n", map.z_min, map.z_max);
	ft_printf("scale=%d offset_x=%d offset_y=%d\n",
		map.scale, map.offset_x, map.offset_y);
	fdf.w = &w_data;
	fdf.map = &map;
	render_iso(&w_data, &map);
	window_loop(&w_data, &fdf);
	return (0);
}
