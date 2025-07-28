#include "../../include/cub3d.h"

char	*get_type(t_type type)
{
	if (type == WALL)
		return("WALL");
	if (type == FLOOR)
		return("FLOOR");
	if (type == PLAYER_E)
		return("PLAYER_E");
	if (type == PLAYER_W)
		return("PLAYER_W");
	if (type == PLAYER_N)
		return("PLAYER_N");
	if (type == PLAYER_S)
		return("PLAYER_S");
	if (type == VOID)
		return("VOID");
	return ("");
}

void	print_matrix(t_game *data)
{
	int	i;

	if (!data->map)
		return ;
	i = -1;
	ft_printf("Map Width:%d\n", data->map_width);
	ft_printf("Map Height:%d\n", data->map_height);
	ft_printf("[Map matrix]\n");
	while (data->map[++i])
		ft_printf("%s\n", data->map[i]);
}

void	print_map(t_game *data)
{
	size_t	i;
	size_t	j;

	if (!data->matrix)
		return ;
	i = 0;
	ft_printf("Game Map:\n");
	while (i < data->map_height)
	{
		j = 0;
		while (j < data->map_width)
		{
			ft_printf("[%s]", get_type(data->matrix[i][j].type));
			j++;
		}
		ft_printf("\n");
		i++;
	}
}