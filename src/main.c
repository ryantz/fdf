/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryatan <ryatan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 09:27:16 by ryatan            #+#    #+#             */
/*   Updated: 2026/04/27 21:44:03 by ryatan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// malloc used here
// 700 x 700
// 10 - 690 (68 points)



int	main(void)
{
	t_outer_array outer;

	parse_map(HOME_PATH, &outer);
	render_2d_grid(outer.outer_array);
	return (0);
}
