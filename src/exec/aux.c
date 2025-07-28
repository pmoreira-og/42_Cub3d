#include "../../include/cub3d.h"

double	ft_min(double n1, double n2)
{
	if (n1 < n2)
		return (n1);
	return (n2);
}

void	put_pixel(t_img_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->len + x * (data->bpp / 8));
	*(unsigned int *)dst = color;
}

void	get_scale(t_game *game)
{
	game->scale = ft_min((WIDTH / game->map_width),
			(HEIGHT / game->map_height));
}
