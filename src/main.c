/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryatan <ryatan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 09:27:16 by ryatan            #+#    #+#             */
/*   Updated: 2026/05/08 09:54:39 by ryatan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(int argc, char **argv)
{
	t_outer_array	outer;
	t_map			map;
	t_win_data		w_data;
	t_fdf			fdf;

	if (error_checks(argc, argv) == 1)
		return (1);
	if (!parse_map_2d(argv[1], &outer))
		return (print_error(WRONG_MAP_FORMAT), 1);
	if (!parse_map_3d(outer.outer_array, &map))
	{
		free_all(outer.outer_array);
		return (print_error(WRONG_MAP_FORMAT), 1);
	}
	free_all(outer.outer_array);
	w_data = init_win_data();
	find_z_range(&map, &(map.z_min), &(map.z_max));
	compute_scale(&map, &w_data);
	fdf.w = &w_data;
	fdf.map = &map;
	render_iso(&w_data, &map);
	window_loop(&w_data, &fdf);
	return (0);
}
