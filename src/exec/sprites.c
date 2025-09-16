#include "../../include/cub3d.h"

bool	get_sprite_data(t_game *g, t_img_data *ptr, char *path)
{
	ptr->img = mlx_xpm_file_to_image(g->mlx, path, &ptr->width, &ptr->height);
	if (!ptr->img)
		return (false);
	ptr->addr = mlx_get_data_addr(ptr->img, &ptr->bpp, &ptr->len, &ptr->endian);
	if (!ptr->addr)
		return (false);
	return (true);
}

void	put_pixel(t_img_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->len + x * (data->bpp / 8));
	*(unsigned int *)dst = color;
}

int	get_pixel(t_img_data *img, int x, int y)
{
	char	*dst;

	if (x < 0 || y < 0 || x > img->width || y > img->height)
		return (0);
	dst = img->addr + (y * img->len + x * (img->bpp / 8));
	return (*(unsigned int *)dst);
}

void	sprite_to_bg(t_img_data *bg, t_img_data *sprite, t_cord sprt, t_cord win)
{
	unsigned int	color;
	int				wid;
	int				hei;

	hei = -1;
	while (++hei < sprt.y)
	{
		wid = -1;
		while (++wid < sprt.x)
		{
			color = get_pixel(sprite, wid, hei);
			if (color != TRANSPARENT)
				put_pixel(bg, win.x + wid, win.y + hei, color);
		}
	}
}
