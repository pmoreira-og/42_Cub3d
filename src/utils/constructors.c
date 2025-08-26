#include "../../include/cub3d.h"

t_img_data	*get_img(t_game *game, int width, int height)
{
	t_img_data	*img;

	img = ft_calloc(1, sizeof(t_img_data));
	if (!img)
		return (printf_fd(2, "img alloc error\n"), NULL);
	img->img = mlx_new_image(game->mlx, width, height);
	if (!img->img)
		return (free(img), printf_fd(2, "mlx img error\n"), NULL);
	img->addr = mlx_get_data_addr(img->img, &img->bpp,
			&img->len, &img->endian);
	if (!img->addr)
		return (free(img), printf_fd(2, "mlx img addr error\n"), NULL);
	return (img);
}
