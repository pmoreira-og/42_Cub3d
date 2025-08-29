#include "../../include/cub3d.h"

static t_img_data	*get_wall_text(t_game *g, t_dda *dda)
{
	if (dda->side == 0)
	{
		if (dda->ray_dir_x > 0)
			return (&g->walls[1]);
		else
			return (&g->walls[3]);
	}
	else
	{
		if (dda->ray_dir_y > 0)
			return (&g->walls[2]);
		else
			return (&g->walls[0]);
	}
}

static void	init_wall(t_player *p, t_dda *dda, t_wall *w)
{
	if (dda->side == 0)
		w->wall_x = p->pos_y + dda->perp_dist * dda->ray_dir_y;
	else
		w->wall_x = p->pos_x + dda->perp_dist * dda->ray_dir_x;
	w->wall_x -= floor(w->wall_x);
	w->tex_x = (int)(w->wall_x * w->texture->width);
	if (dda->side == 0 && dda->ray_dir_x > 0)
		w->tex_x = w->texture->width - w->tex_x - 1;
	if (dda->side == 1 && dda->ray_dir_y < 0)
		w->tex_x = w->texture->width - w->tex_x - 1;
}

static void	get_wall_step(t_game *g, t_wall *wall, t_dda *dda)
{
	if (dda->perp_dist < 0.000001)
		dda->perp_dist = 0.000001;
	wall->height = (int)(HEIGHT / dda->perp_dist);
	wall->start = -wall->height / 2 + HEIGHT / 2;
	wall->end = wall->height / 2 + HEIGHT / 2;
	if (wall->end >= HEIGHT)
		wall->end = HEIGHT - 1;
	wall->texture = get_wall_text(g, dda);
	wall->step = (double)wall->texture->height / (double)wall->height;
	wall->tex_pos = 0;
	if (wall->start < 0)
	{
		wall->tex_pos = (-wall->start) * wall->step;
		wall->start = 0;
	}
}

/// @brief Draw the vertical section of the wall
/// @param g Game struct.
/// @param perpWallDist Dist between the player and the object.
/// @param x X position on the screen to draw.
static void	draw_wall(t_game *g, t_dda *dda, int x, t_wall *wall)
{
	int	y;

	put_pixel(&g->bg, x, wall->start, 0);
	y = wall->start + 1;
	while (y <= wall->end)
	{
		wall->tex_y = (int)wall->tex_pos;
		if (wall->tex_y >= wall->texture->height)
			wall->tex_y = wall->texture->height - 1;
		wall->tex_pos += wall->step;
		wall->color = get_pixel(wall->texture, wall->tex_x, wall->tex_y);
		if (dda->side == 1)
			wall->color = (wall->color >> 1) & 0x7F7F7F;
		put_pixel(&g->bg, x, y, wall->color);
		y++;
	}
	put_pixel(&g->bg, x, wall->end, 0);
}

void	draw_section(t_game *g, t_dda *dda, int x, t_player *p)
{
	int		y;
	t_wall	wall;

	y = -1;
	get_wall_step(g, &wall, dda);
	init_wall(p, dda, &wall);
	while (++y < wall.start)
		put_pixel(&g->bg, x, y, g->ceiling_color);
	draw_wall(g, dda, x, &wall);
	y = wall.end;
	while (++y < HEIGHT)
		put_pixel(&g->bg, x, y, g->floor_color);
}
