#include "fdf.h"

int	main(void)
{
	int	fd;
	const char *path = "/home/ryatan/core/fdf_home/test_maps/42.fdf";
	char	*line;

	fd = open(path, O_RDONLY);
	ft_printf("%d", fd);
	line = get_next_line(fd);
	ft_printf("%s", line);
	return (0);
}
