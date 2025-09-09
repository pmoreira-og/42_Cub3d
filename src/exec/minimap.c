#include "../../include/cub3d.h"

void	init_minimap(t_game *g)
{
	g->mini.offset = 25;
	g->mini.width = WIDTH * 0.22;
	g->mini.height = HEIGHT * 0.22;
	g->mini.tile = ft_min((g->mini.width / g->map_width),
			(g->mini.height / g->map_height));
}

void	render_minimap(t_game *game)
{
	colorblock_to_bg(game, 808080, (t_cord){game->mini.width, game->mini.height}, \
	(t_cord){game->mini.offset, game->mini.offset});
	
	int center_x =  game->mini.width / 2 + game->mini.offset;
	int center_y =  game->mini.height / 2 + game->mini.offset;
	t_cord left = collider_angle(game->player.direction + deg2rad(33), 80, game, center_x, center_y);
	t_cord right = collider_angle(game->player.direction - deg2rad(33), 80, game, center_x, center_y);
	draw_line(game, left, right);
	//collider_angle(game->player.direction + deg2rad(33), 500, game, (t_cord){center_x, center_y});
	// fill_border(game);
	// draw_grid(game, &p);
	// draw_player(game, &p);
	// draw_rays(game, &p);
}

/* void	fill_border(t_game *g)
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
} */

void	colorblock_to_bg(t_game *game, int color, t_cord area, t_cord win)
{
	int	wid;
	int	hei;

	hei = -1;
	while (++hei < area.y)
	{
		wid = -1;
		while (++wid < area.x)
		{
			if (hei < 3 || hei > area.y - 4 || wid < 3 || wid > area.x - 4)
				put_pixel(&game->bg, win.x + wid, win.y + hei, 0);
			else
				put_pixel(&game->bg, win.x + wid, win.y + hei, color);
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