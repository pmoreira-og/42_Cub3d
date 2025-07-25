#include "../../include/cub3d.h"

t_img_data	*get_img(t_game *game)
{
	t_img_data	*img;

	img = ft_calloc(1, sizeof(t_img_data));
	if (!img)
		return (printf_fd(2, "img alloc error\n"), NULL);
	img->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (!img->img)
		return (free(img), printf_fd(2, "mlx img error\n"), NULL);
	img->addr = mlx_get_data_addr(img->img, &img->bpp,
			&img->len, &img->endian);
	if (!img->addr)
		return (free(img), printf_fd(2, "mlx img addr error\n"), NULL);
	return (img);
}

bool	init_map(t_game *data)
{
	int	i;

	i = -1;
	while(data->map[++i])
	{
		if (ft_strlen(data->map[i]) > data->map_width)
			data->map_width = ft_strlen(data->map[i]);
	}
	data->map_height = i;
	i = -1;
	return (1);
}

void	init_data(t_game *data, char **map)
{
	if (!map)
		return ;
	ft_bzero(data, sizeof(t_game));
	data->mlx = mlx_init();
	if (!data->mlx)
		return (merror("data.mlx"));
	data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "Cub3d Ultimate");
	if (!data->win)
		return (free(data->mlx), merror("data.win"));
	data->bg = get_img(data);
	if (!data->bg)
	{
		mlx_destroy_window(data->mlx, data->win);
		return (free(data->mlx), merror("data.bg.img"));
	}
	data->map = copy_map(map);
	init_map(data);
}
