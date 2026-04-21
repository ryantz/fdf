#include "fdf.h"

int	close_handler(t_win_data *w_data)
{
	mlx_destroy_window(w_data->mlx, w_data->win);
	return (0);
}

int	main(void)
{
	int			fd;
	const char *path = "/home/ryatan/core/fdf_home/test_maps/42.fdf";
	//const char *path = "/home/ryantz/dev/42/fdf/test_maps/42.fdf";
	char		*line;
	t_win_data w_data;

	fd = open(path, O_RDONLY);
	ft_printf("%d", fd);
	while (1)
	{
		line = get_next_line(fd);
		if (line != NULL)
		{
			ft_printf("%s", line);
			free(line);
		}
		else
			break;
	}
	close(fd);
	w_data.mlx = mlx_init();
	w_data.win = mlx_new_window(w_data.mlx, 700, 700, "new window");
	mlx_hook(w_data.win, 17, 0, close_handler, &w_data);
	mlx_loop(w_data.mlx);
	return (0);
}
