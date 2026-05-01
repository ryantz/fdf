/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryatan <ryatan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 09:27:16 by ryatan            #+#    #+#             */
/*   Updated: 2026/05/01 14:33:55 by ryatan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// malloc used here
// 700 x 700
// 10 - 690 (68 points)



int	main(void)
{
	t_outer_array	outer;
	t_map			map;
	t_win_data		w_data;

	parse_map_2d(HOME_PATH, &outer);
	parse_map_3d(outer.outer_array, &map);
	print_map_3d(&map);
	free_all(outer.outer_array);
	w_data = init_win_data();
	render_iso(&w_data, &map);
	window_loop(&w_data);
	return (0);
}
