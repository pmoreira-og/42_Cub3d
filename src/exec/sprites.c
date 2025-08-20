#include "../../include/cub3d.h"

char	*get_sprite_data(t_game *g, char *path)
{
	t_img_data	texture;
	int			width;
	int			height;

	texture.img = mlx_xpm_file_to_image(g->mlx, path, &width, &height);

	texture.addr = mlx_get_data_addr(texture.img, &texture.bpp,
			&texture.len, &texture.endian);
	if (!texture.addr)
		return (NULL);
	mlx_put_image_to_window(g->mlx, g->win, texture.img, 0, HEIGHT * 0.8);

	return (texture.addr);
}