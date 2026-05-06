/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryatan <ryatan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 11:49:52 by ryatan            #+#    #+#             */
/*   Updated: 2026/05/06 20:47:28 by ryatan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# define HOME_PATH "/home/ryantz/dev/42/fdf/test_maps/" 
# define PATH "/home/ryatan/core/fdf_home/test_maps/"
# define WHITE 0xFFFFFF
# define RED 0xFF0000

# include <math.h>
# include <fcntl.h>

# include "libft.h"
# include "ft_printf.h"
# include "mlx.h"
# include "mlx_int.h"
# include "../get_next_line/get_next_line.h"

typedef struct s_win_data
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*addr;
	int			bpp;
	int			line_len;
	int			endian;
	int			win_w;
	int			win_h;
}	t_win_data;

typedef struct s_point
{
	int			x;
	int			y;
}	t_point;

typedef struct s_int_array
{
	int			*array;
	int			count;
}	t_int_array;

typedef struct s_map
{
	t_int_array	*rows_array;
	int			rows;
	int			cols;
	int			scale;
	int			offset_x;
	int			offset_y;
	int			**colors;
	int			z_min;
	int			z_max;
}	t_map;

typedef struct s_bres
{
	int			dx;
	int			dy;
	int			err;
	int			e2;
}	t_bres;

typedef struct s_outer_array
{
	char	**outer_array;
	int		line_count;
}	t_outer_array;

typedef struct s_fdf
{
	t_win_data	*w;
	t_map		*map;
}	t_fdf;

void		free_all(char **array);
void		free_map(t_map *map);
void		print_map_3d(t_map *map);
int			parse_map_3d(char **outer_array, t_map *map);
int			split_rows(char *outer_array_row, t_int_array *z_array,
				int **colors_row);
t_win_data	init_win_data(void);
int			window_close_handler(t_fdf *fdf);
void		window_loop(t_win_data *w_data, t_fdf *fdf);
char		**parse_map_2d(char *map_file_path, t_outer_array *outer);

void		render_iso(t_win_data *w, t_map *map);
void		bresenham(t_win_data *w, t_point p0, t_point p1, int color);
t_point		project(int x, int y, int z, t_map *map);
int			hex_to_dec(char *str);
void		put_pixel(t_win_data *w_data, int x, int y, int color);
void		compute_scale(t_map *map, t_win_data *w);
void		find_z_range(t_map *map, int *z_min, int *z_max);

#endif
