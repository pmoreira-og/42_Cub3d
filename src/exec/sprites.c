#include "../../include/cub3d.h"

bool	get_sprite_data(t_game *g, t_img_data *ptr, char *path)
{

	ptr->img = mlx_xpm_file_to_image(g->mlx, path, &ptr->width, &ptr->height);
	if(!ptr->img)
		return (false);
	ptr->addr = mlx_get_data_addr(ptr->img, &ptr->bpp, &ptr->len, &ptr->endian);
	if (!ptr->addr)
		return (false);
	return (true);
}

bool	load_walls(t_game *g)
{
	if(!get_sprite_data(g, &g->walls[0], "./textures/north.xpm"))
		return (false);
	if(!get_sprite_data(g, &g->walls[1], "./textures/easter_egg.xpm"))
		return (false);
	if(!get_sprite_data(g, &g->walls[2], "./textures/duck.xpm"))
		return (false);
	if(!get_sprite_data(g, &g->walls[3], "./textures/logo_cub3d.xpm"))
		return (false);
	return (true);
}
