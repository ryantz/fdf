#include "fdf.h"

int	main(void)
{
	int			line_count;
	char		**map_2d_array;
	t_win_data	w_data;

	line_count = count_lines_in_map(HOME_PATH);
	map_2d_array = malloc((line_count + 1) * sizeof(char *));
	map_2d_array[line_count] = NULL;
	map_2d_array = parse_map(HOME_PATH, line_count, &map_2d_array);
	w_data = init_win_data();
	window_loop(&w_data);
	return (0);
}
