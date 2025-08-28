#include "../../include/cub3d.h"

//! Probably gonna need 1 more param to get the right wall text.
void get_wall_step(t_game *g, t_wall *w, t_dda *dda)
{
    double perp = dda->dist;
    if (perp < 1e-6) perp = 1e-6;

    double lineHeight = (double)HEIGHT / perp;
    w->height = (int)lineHeight;

    int uncut_start = -(int)lineHeight / 2 + HEIGHT / 2;
    int uncut_end   =  (int)lineHeight / 2 + HEIGHT / 2;

    w->start = uncut_start;
    w->end   = uncut_end;
    if (w->start < 0) w->start = 0;
    if (w->end >= HEIGHT) w->end = HEIGHT - 1;

    w->texture = get_wall_text(g, dda);
    w->step    = (double)w->texture->height / lineHeight;
    w->tex_pos = (w->start - uncut_start) * w->step;
}

void init_wall(t_point *p, t_dda *dda, t_wall *w)
{
    double hitX = p->x + dda->dist * dda->ray_dir_x;
    double hitY = p->y + dda->dist * dda->ray_dir_y;

    if (dda->side == 0)
        w->wallX = hitY;
    else
        w->wallX = hitX;
    w->wallX -= floor(w->wallX);

    w->texX = (int)(w->wallX * w->texture->width);
    if (dda->side == 0 && dda->ray_dir_x > 0)
        w->texX = w->texture->width - w->texX - 1;
    if (dda->side == 1 && dda->ray_dir_y < 0)
        w->texX = w->texture->width - w->texX - 1;
}
// void	get_wall_step(t_game *g, t_wall *wall, t_dda *dda)
// {
// 	if (dda->perp_dist < 0.000001)
// 		dda->perp_dist = 0.000001;
// 	wall->height = (int) (HEIGHT/ dda->perp_dist);
// 	wall->start = -wall->height / 2 + HEIGHT / 2;
	
// 	wall->end = wall->height / 2 + HEIGHT / 2;
// 	if (wall->end >= HEIGHT)
// 		wall->end = HEIGHT - 1;
// 	wall->texture = get_wall_text(g, dda);
// 	wall->step = (double)wall->texture->height / (double)wall->height;
// 	wall->tex_pos = 0;
// 	if (wall->start < 0)
// 	{
// 		wall->tex_pos = (-wall->start) * wall->step;
// 		wall->start = 0;
// 	}
// }

// void	init_wall(t_point *p, t_dda *dda, t_wall *wall)
// {
// 	if (dda->side == 0)
// 		wall->wallX = p->y + dda->dist * dda->ray_dir_y;
// 	else
// 		wall->wallX = p->x + dda->dist * dda->ray_dir_x;
// 	wall->wallX -= floor(wall->wallX);
// 	wall->texX = (int)(wall->wallX * (double)wall->texture->width);
// 	if (dda->side == 0 && dda->ray_dir_x > 0)
// 		wall->texX = wall->texture->width - wall->texX - 1;
// 	if (dda->side == 1 && dda->ray_dir_y < 0)
// 		wall->texX= wall->texture->width - wall->texX - 1;
// }

/// @brief Draw the vertical section of the wall
/// @param g Game struct.
/// @param perpWallDist Dist between the player and the object.
/// @param x X position on the screen to draw.
void draw_wall(t_game *g, t_dda *dda, int x, t_wall *wall)
{
	int		y;

	put_pixel(&g->bg, x, wall->start, 0);
	y = wall->start;
	while (y <= wall->end)
	{
		wall->texY = (int)wall->tex_pos;
		if ( wall->texY >= wall->texture->height)
			wall->texY = wall->texture->height - 1;
		wall->tex_pos += wall->step;
		wall->color = get_pixel(wall->texture, wall->texX, wall->texY);
		if (dda->side == 1)
			wall->color = (wall->color >> 1) & 0x7F7F7F;
		put_pixel(&g->bg, x, y, wall->color);
		y++;
	}
	put_pixel(&g->bg, x, wall->end, 0);
}

void	draw_section(t_game *g, t_dda *dda, int x, t_point *p)
{
	int		y;
	t_wall	wall;

	y = -1;
	get_wall_step(g,&wall, dda);
	init_wall(p, dda, &wall);
	while (++y < wall.start)
		put_pixel(&g->bg, x, y, g->ceiling_color);
	draw_wall(g, dda, x, &wall);
	y = wall.end;
	while(++y < HEIGHT)
		put_pixel(&g->bg, x, y, g->floor_color);
}

t_img_data	*get_wall_text(t_game *g, t_dda *dda)
{
	if (dda->side == 0)
	{
		if (dda->ray_dir_x > 0)
			return(&g->walls[1]);
		else
			return(&g->walls[3]);
	}
	else
	{
		if (dda->ray_dir_y > 0)
			return(&g->walls[2]);
		else
			return(&g->walls[0]);
	}
}