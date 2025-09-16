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
	w->dot = p->dir_x * dda->ray_dir_x + p->dir_y * dda->ray_dir_y;
	if (w->dot >= p->cos_flash)
		w->ang_intensity = (w->dot - p->cos_flash) / (1.0 - p->cos_flash);
	else
		w->ang_intensity = 0;
	w->dist_intensity = 1.0 / (1.0 + p->flash_k1 * dda->perp_dist \
+ p->flash_k2 * (pow(dda->perp_dist, 2)));
	w->light = p->ambient + (0.7 + (p->flash_on * 0.25) - p->ambient) \
* w->ang_intensity * w->dist_intensity;
	if (w->light < p->ambient)
		w->light = p->ambient;
	if (w->light > 1)
		w->light = 1;
}

static void	get_wall_step(t_game *g, t_wall *wall, t_dda *dda, t_player *p)
{
	if (dda->perp_dist < 0.000001)
		dda->perp_dist = 0.000001;
	wall->height = (int)(HEIGHT / dda->perp_dist);
	wall->start = -wall->height / 2 + HEIGHT / 2;
	wall->end = wall->height / 2 + HEIGHT / 2;
	wall->end -= (int)p->bob.cam_pitch;
	wall->start -= (int)p->bob.cam_pitch;
	wall->end += p->vertical_view;
	wall->start += p->vertical_view;
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
static void	draw_wall(t_game *g, int x, t_wall *wall)
{
	int	y;

	y = wall->start;
	while (y <= wall->end)
	{
		wall->tex_y = (int)wall->tex_pos;
		if (wall->tex_y >= wall->texture->height)
			wall->tex_y = wall->texture->height - 1;
		wall->tex_pos += wall->step;
		wall->color = get_pixel(wall->texture, wall->tex_x, wall->tex_y);
		put_pixel(&g->bg, x, y, apply_light(wall->color, wall->light));
		y++;
	}
}

/* 
		put_pixel(&g->bg, x, y,g->floor_color >> 1 & 0x7f7f7f);
		put_pixel(&g->bg, x, y, g->ceiling_color >> 1 & 0x7f7f7f);

 */

void	draw_section(t_game *g, t_dda *dda, int x, t_player *p)
{
	int		y;
	t_wall	wall;

	y = -1;
	get_wall_step(g, &wall, dda, p);
	init_wall(p, dda, &wall);
	while (++y < wall.start - 1)
		put_pixel(&g->bg, x, y, apply_light(g->ceiling_color, get_light(y, p)));
	put_pixel(&g->bg, x, y, 0);
	draw_wall(g, x, &wall);
	put_pixel(&g->bg, x, wall.end + 1, 0);
	y = wall.end + 1;
	while (++y < HEIGHT)
		put_pixel(&g->bg, x, y, apply_light(g->floor_color, get_light(y, p)));
}
