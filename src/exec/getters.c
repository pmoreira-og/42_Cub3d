
#include "../../include/cub3d.h"

bool	is_player(t_point *ptr)
{
	if (!ptr)
		return (false);
	if (ptr->type == PLAYER_E)
		return (true);
	if (ptr->type == PLAYER_W)
		return (true);
	if (ptr->type == PLAYER_N)
		return (true);
	if (ptr->type == PLAYER_S)
		return (true);
	return (false);
}

void	find_player(t_game *game, t_point *save)
{
	size_t	y;
	size_t	x;

	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (x < game->map_width)
		{
			if (is_player(&game->matrix[y][x]))
			{
				if (save)
					*save = game->matrix[y][x];
				return ;
			}
			x++;
		}
		y++;
	}
	if (save)
		save = NULL;
}

double	ft_min(double n1, double n2)
{
	if (n1 < n2)
		return (n1);
	return (n2);
}

int	get_pixel(t_img_data *img, int x, int y)
{
	char	*dst;

	dst = img->addr + (y * img->len + x * (img->bpp / 8));
	return (*(unsigned int *)dst);
}
