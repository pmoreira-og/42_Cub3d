#include "../../include/cub3d.h"

void	ft_freed(void **ptr, int size)
{
	if (!ptr || size < 0)
		return ;
	while (size > 0)
		free(ptr[--size]);
	free(ptr);
}

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

void	clean_mlx(t_game *data)
{
	if (data->bg.img)
		mlx_destroy_image(data->mlx, data->bg.img);
	if (data->walls[0].img)
		mlx_destroy_image(data->mlx, data->walls[0].img);
	if (data->walls[1].img)
		mlx_destroy_image(data->mlx, data->walls[1].img);
	if (data->walls[2].img)
		mlx_destroy_image(data->mlx, data->walls[2].img);
	if (data->walls[3].img)
		mlx_destroy_image(data->mlx, data->walls[3].img);
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	if (data->mlx)
		mlx_destroy_display(data->mlx);
	free(data->mlx);
}

void	armageddon(t_game *data)
{
	if (data->mlx)
		clean_mlx(data);
	if (data->matrix)
		free_matrix((void **)data->matrix);
	free (data->paths[0]);
	free (data->paths[1]);
	free (data->paths[2]);
	free (data->paths[3]);
}
