#include "../../include/cub3d.h"

void	clean_matrix(char **matrix)
{
	int	i;
	if (!matrix)
		return ;
	i = -1;
	while (matrix[++i])
		free(matrix[i]);
	free(matrix);
}

void	armageddon(t_game *data)
{
	if (data->file_fd > 2)
		close(data->file_fd);
	if (data->map)
		clean_matrix(data->map);
	if (data->mlx)
	{
		if (data->bg->img)
		{
			mlx_destroy_image(data->mlx, data->bg->img);
			free(data->bg);
		}
		if (data->win)
			mlx_destroy_window(data->mlx, data->win);
		if (data->mlx)
			mlx_destroy_display(data->mlx);
		free(data->mlx);
	}
}