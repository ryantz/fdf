/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryatan <ryatan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 11:49:52 by ryatan            #+#    #+#             */
/*   Updated: 2026/04/25 11:38:09 by ryatan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# define HOME_PATH "/home/ryantz/dev/42/fdf/test_maps/42.fdf" 
# define PATH "/home/ryatan/core/fdf_home/test_maps/42.fdf"
# define WHITE_COLOR 26777215

# include <math.h>
# include <fcntl.h>

# include "libft.h"
# include "ft_printf.h"
# include "mlx.h"
# include "mlx_int.h"
# include "../get_next_line/get_next_line.h"

typedef struct	s_outer_array
{
	char	**outer_array;
	int		line_count;
}	t_outer_array;

typedef struct	s_win_data
{
	void	*mlx;
	void	*win;
}	t_win_data;

typedef struct	s_2d_coord
{
	int	x;
	int	y;
	int	color;
}	t_2d_coord;

int render_loop(void);

t_win_data	init_win_data(void);
int			window_close_handler(t_win_data *w_data);
void		window_loop(t_win_data *w_data);

char	**parse_map(char *map_file_path, t_outer_array *outer);
#endif
