#include "../../include/cub3d.h"

void	init_minimap(t_game *g)
{
	g->mini.show = true;
	g->mini.bg = &g->bg;
	g->mini.p = &g->player;
	g->mini.m = &g->matrix;
	g->mini.m_h = g->map_height;
	g->mini.m_w = g->map_width;
	g->mini.scale = 1;
	update_minimap_vals(&g->mini);
}

/// @brief sets the minimap values according to scale
/// @param mini struct with all needed values for the minimap
void	update_minimap_vals(t_minimap *mini)
{
	mini->offset = 28 * mini->scale;
	mini->size.x = (WIDTH * 0.22) * mini->scale;
	mini->size.y = (HEIGHT * 0.22) * mini->scale;
	mini->center.x = mini->size.x / 2 + mini->offset;
	mini->center.y = mini->size.y / 2 + mini->offset;
}

/// @brief puts the minimap on screen according to the players pos/dir
/// @param mini struct with all needed values for the minimap
void	render_minimap(t_minimap mini)
{
	t_cord	dir_os;

	update_minimap_vals(&mini);
	draw_colorblock(mini.bg, 0x090B0A, mini.size, (t_cord){mini.offset,
		mini.offset});
	draw_colorframe(mini.bg, 0x363930, (t_cord){mini.size.x + 6, mini.size.y
		+ 6}, (t_cord){mini.offset - 3, mini.offset - 3});
	draw_minimap_tiles(mini, (t_cord){mini.p->pos.x - 4 * mini.scale,
		mini.p->pos.y - 3 * mini.scale}, (t_cord){mini.center.x - 50
		* (mini.p->pos.x - floor(mini.p->pos.x) + 4 * mini.scale), mini.center.y
		- 50 * (mini.p->pos.y - floor(mini.p->pos.y) + 3 * mini.scale)});
	draw_angled_line(mini.bg, mini.center, mini.p->direction + deg2rad(33), 80);
	draw_angled_line(mini.bg, mini.center, mini.p->direction - deg2rad(33), 80);
	draw_circle(mini.bg, (t_circle){mini.center, mini.p->direction
		+ deg2rad(33), mini.p->direction - deg2rad(33), 80, 0xFBFE8D});
	dir_os = (t_cord){cos(mini.p->direction) * 4, -sin(mini.p->direction) * 4};
	bucket_tool(mini.bg, (t_cord){mini.center.x + dir_os.x, mini.center.y
		+ dir_os.y}, 0x363930, 0x223030);
	draw_circle(mini.bg, (t_circle){mini.center, 0, 2 * PI, 12, 0xC0BA3E});
	bucket_tool(mini.bg, (t_cord){mini.center.x - dir_os.x, mini.center.y
		- dir_os.y}, 0xFBFE36, 0x223030);
	bucket_tool(mini.bg, (t_cord){mini.center.x + dir_os.x, mini.center.y
		+ dir_os.y}, 0xFBFE36, 0x363930);
}

/// @brief draws all floor and wall map tiles within a radius of the player
/// @param mini struct with all needed values for the minimap
/// @param map_cord cordinates in the map from where to start
/// @param win_cord cordinates in the window where to start drawing
void	draw_minimap_tiles(t_minimap mini, t_cord map_cord, t_cord win_cord)
{
	t_cord	area;

	while (map_cord.y < mini.m_h && win_cord.y <= mini.offset + mini.size.y)
	{
		area.y = 50;
		if (map_cord.y >= 0)
		{
			if (win_cord.y < mini.offset)
			{
				area.y -= mini.offset - win_cord.y;
				win_cord.y = mini.offset;
			}
			if (win_cord.y + area.y > mini.offset + mini.size.y)
				area.y -= (win_cord.y + area.y) - (mini.offset + mini.size.y);
			draw_minimap_row(mini, map_cord, win_cord, area);
		}
		map_cord.y++;
		win_cord.y += area.y;
	}
}

/// @brief draws map row indicated by MAP_CORD
void	draw_minimap_row(t_minimap mini, t_cord map_cord, t_cord win_cord,
		t_cord area)
{
	while (map_cord.x < mini.m_w && win_cord.x <= mini.offset + mini.size.x)
	{
		area.x = 50;
		if (map_cord.x >= 0)
		{
			if (win_cord.x < mini.offset)
			{
				area.x -= mini.offset - win_cord.x;
				win_cord.x = mini.offset;
			}
			if (win_cord.x + area.x > mini.offset + mini.size.x)
				area.x -= (win_cord.x + area.x) - (mini.offset + mini.size.x);
			if ((*mini.m)[(int)map_cord.y][(int)map_cord.x].type == WALL)
				draw_colorblock(mini.bg, 0x9DD1E0, area, win_cord);
			if (valid_move(&(*mini.m)[(int)map_cord.y][(int)map_cord.x]))
				draw_colorblock(mini.bg, 0x223030, area, win_cord);
		}
		map_cord.x++;
		win_cord.x += area.x;
	}
}
