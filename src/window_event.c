#include "fdf.h"

t_win_data	init_win_data(void)
{
	t_win_data	w_data;

	w_data.mlx = mlx_init();
	w_data.win = mlx_new_window(w_data.mlx, 700, 700, "ryatan's fdf");
	w_data.img = mlx_new_image(w_data.mlx, 700, 700);
	w_data.addr = mlx_get_data_addr(w_data.img, &w_data.bpp, &w_data.line_len,
			&w_data.endian);
	return (w_data);
}

int	window_close_handler(t_win_data *w_data)
{
	if (!w_data->mlx || !w_data->win)
		return (0);
	mlx_destroy_window(w_data->mlx, w_data->win);
	exit(1);
	return (1);
}

void	window_loop(t_win_data *w_data)
{
	mlx_hook(w_data->win, 17, 0, window_close_handler, w_data);
	mlx_loop(w_data->mlx);
}
