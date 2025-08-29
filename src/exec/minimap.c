#include "../../include/cub3d.h"

void	init_minimap(t_game *g)
{
	g->mini.offset = 10;
	g->mini.width = WIDTH * 0.2;
	g->mini.height = HEIGHT * 0.2;
	g->mini.tile = ft_min((g->mini.width / g->map_width),
			(g->mini.height / g->map_height));
}

void	fill_border(t_game *g)
{
	int	x;
	int	y;
	int	new_x;
	int	new_y;

	y = -1;
	while (++y < g->mini.height + 2)
	{
		x = -1;
		while (++x < g->mini.width + 2)
		{
			new_x = g->mini.offset + x ;
			new_y = g->mini.offset + y ;
			if (new_x < g->mini.offset + 3 || new_x > g->mini.width +3)
				put_pixel(&g->bg, new_x, new_y, 0);
			if (new_y < g->mini.offset + 3 || new_y > g->mini.height +3)
				put_pixel(&g->bg, new_x, new_y, 0);

			// if ((new_x < 3 || new_x > g->mini.width)
			// 	|| (new_y < 3 || new_y > g->mini.height))
		}
	}
}

// void	draw_grid(t_game *g, t_player *p)
// {

// }

// void	draw_player(t_game *g, t_player *p)
// {

// }

// void	draw_rays(t_game *g, t_player *p)
// {

// }