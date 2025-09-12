#include "../../include/cub3d.h"

void	init_minimap(t_game *g)
{
	g->mini.bg = &g->bg;
	g->mini.p = &g->player;
	g->mini.sc = &g->scene;
	g->mini.m = &g->matrix;
	g->mini.m_h = g->map_height;
	g->mini.m_w = g->map_width;
	g->mini.offset = 25;
	g->mini.width = WIDTH * 0.22;
	g->mini.height = HEIGHT * 0.22;
	g->mini.center.x = g->mini.width / 2 + g->mini.offset;
	g->mini.center.y = g->mini.height / 2 + g->mini.offset;
	g->mini.scale = 1;
}

void	render_minimap(t_minimap mini)
{
	// t_cord left;
	// t_cord right;
	// -- step 1: blank minimap area

	// !!!!!!!!! do a make frame FT
	colorblock_to_bg(mini.bg, 808080, (t_cord){mini.width, mini.height},
	(t_cord){mini.offset, mini.offset});
	colorframe_to_bg(mini.bg, 0, (t_cord){mini.width + 6, mini.height + 6},
	(t_cord){mini.offset - 3, mini.offset - 3});
	
	// -- step 2: draw walls and floor
	//printf("wid : %d, hei : %d\n", mini.width, mini.height);
	//printf("wid/50 : %d, hei/50 : %d\n", mini.width / 50, mini.height / 50);
	draw_minimap_tiles(mini, (t_cord){mini.p->pos_x, mini.p->pos_y}, \
		(t_cord){mini.center.x - 50 * (mini.p->pos_x - floor(mini.p->pos_x)), \
		mini.center.y - 50 * (mini.p->pos_y - floor(mini.p->pos_y))});
	
	// -- step 3: draw the player FOV
	// left =
	collider_angle(mini.bg, mini.center, mini.p->direction + deg2rad(33), 80);
	// right =
	collider_angle(mini.bg, mini.center, mini.p->direction - deg2rad(33), 80);
	draw_circle(mini.bg, mini.center, (t_cord){mini.p->direction + deg2rad(33),
		mini.p->direction - deg2rad(33)}, 80);
	draw_circle(mini.bg, mini.center, (t_cord){0, 2 * PI}, 15);
	//printf("pos y: %f, pos x: %f\n", mini.p->pos_y, mini.p->pos_x);
	//printf(". y: %f, . x: %f\n", mini.p->pos_y - floor(mini.p->pos_y), mini.p->pos_x - floor(mini.p->pos_x));
	//printf("pos y: %d, pos x: %d\n", (int)mini.p->pos_y, (int)mini.p->pos_x);
	//printf("cur spot: %s\n", get_type_print((*mini.m)[(int)mini.p->pos_y][(int)mini.p->pos_x].type));
}

void	draw_minimap_tiles(t_minimap mini, t_cord map_cord, t_cord win_cord)
{
	t_type type;
	t_cord area;
	double win_temp;
	double map_temp;
	
	map_cord.y -= 3;
	win_cord.y -= 3 * 50;
	map_cord.x -= 4;
	win_cord.x -= 4 * 50;
	//printf("\nmap cord x: %f, mini m w: %d\n", map_cord.x, mini.m_w);
	//printf("win cord x: %f, mini offset + mini width: %d\n", win_cord.x, mini.offset + mini.width);
	win_temp = win_cord.x;
	map_temp = map_cord.x;
	while (map_cord.y < mini.m_h && win_cord.y <= mini.offset + mini.height)
	{
		area.y = 50;
		if (map_cord.y >= 0)
		{
			if (win_cord.y < mini.offset)
			{
				area.y -= mini.offset - win_cord.y; 
				win_cord.y = mini.offset;
			}
			if (win_cord.y + area.y > mini.offset + mini.height)
				area.y -= (win_cord.y + area.y) - (mini.offset + mini.height); 
			while (map_cord.x < mini.m_w && win_cord.x <= mini.offset + mini.width)
			{
				//printf("win cord x: %f\n", win_cord.x);
				area.x = 50;
				if (map_cord.x >= 0)
				{
					if (win_cord.x < mini.offset)
					{
						area.x -= mini.offset - win_cord.x; 
						win_cord.x = mini.offset;
					}
					if (win_cord.x + area.x > mini.offset + mini.width)
						area.x -= (win_cord.x + area.x) - (mini.offset + mini.width); 
					type = (*mini.m)[(int)map_cord.y][(int)map_cord.x].type;
					if (type == WALL)
						colorblock_to_bg(mini.bg, 20, area, win_cord);
					if (type >= FLOOR && type <= PLAYER_W)
						colorblock_to_bg(mini.bg, 80808, area, win_cord);
				}
				map_cord.x++;
				win_cord.x += area.x;
			}
			win_cord.x = win_temp;
			map_cord.x = map_temp;
		}
		map_cord.y++;
		win_cord.y += area.y;
	}
}

void	colorblock_to_bg(t_img_data *bg, int color, t_cord area, t_cord win)
{
	int	wid;
	int	hei;

	hei = -1;
	while (++hei < area.y)
	{
		wid = -1;
		while (++wid < area.x)
		{
			put_pixel(bg, win.x + wid, win.y + hei, color);
		}
	}
}

void	colorframe_to_bg(t_img_data *bg, int color, t_cord area, t_cord win)
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
				put_pixel(bg, win.x + wid, win.y + hei, color);
		}
	}
}
