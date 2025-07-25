#include "../../include/cub3d.h"

void	print_game_data(t_game *data)
{
	int	i;

	i = -1;
	ft_printf("Map Width:%d\n", data->map_width);
	ft_printf("Map Height:%d\n", data->map_height);
	ft_printf("[Map matrix]\n");
	while (data->map[++i])
		ft_printf("%s\n", data->map[i]);
	
}

/// @brief Prints malloc error message on stderr.
/// @param msg Message for malloc debug porposes.
void	merror(char *msg)
{
	if (msg)
		printf_fd(2, "Malloc:%s\n", msg);
}

