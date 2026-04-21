#include "fdf.h"

int	main(void)
{
	int	fd;
	//const char *path = "/home/ryatan/core/fdf_home/test_maps/42.fdf";
	const char *path = "/home/ryantz/dev/42/fdf/test_maps/42.fdf";
	char	*line;
	t_xvar *mlx_ptr;

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
	}
	mlx_ptr = mlx_init();
	mlx_new_window(mlx_ptr, 100, 100, "new window");
	mlx_loop(mlx_ptr);
	return (0);
}
