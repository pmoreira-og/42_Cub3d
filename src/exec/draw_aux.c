#include "../../include/cub3d.h"

//! Probably gonna need 1 more param to get the right wall text.

void	get_wall_step(t_game *g, t_wall *wall, t_dda *dda, int height)
{
	wall->texture = get_wall_text(g, dda);
	wall->step = (double)wall->texture->height / (double)height;
}

void	init_wall(t_point *p, t_dda *dda, t_game *g, t_wall *wall)
{
	(void) g;
	if (dda->side == 0)
		wall->wallX = p->y + dda->dist * dda->ray_dir_y;
	else
		wall->wallX = p->x + dda->dist * dda->ray_dir_x;
	wall->wallX -= floor(wall->wallX);
	wall->texX = (int)(wall->wallX * (double)wall->texture->width);
	if (dda->side == 0 && dda->ray_dir_x > 0)
		wall->texX = wall->texture->width - wall->texX - 1;
	if (dda->side == 1 && dda->ray_dir_y < 0)
		wall->texX= wall->texture->width - wall->texX - 1;
	wall->tex_pos = 0;
}

/// @brief Draw the vertical section of the wall
/// @param g Game struct.
/// @param perpWallDist Dist between the player and the object.
/// @param x X position on the screen to draw.
void draw_section(t_game *g, t_dda *dda, int x, t_point *p)
{
	int		start;
	int		end;
	int		height;
	int		y;
	t_wall	wall;

	if (dda->dist < 1e-6)
		dda->dist = 1e-6;
	height = (int) (HEIGHT/ dda->dist);
	start = -height / 2 + HEIGHT / 2;
	if (start < 0)
		start = 0;
	end = height / 2 + HEIGHT / 2;
	if (end >= HEIGHT)
		end = HEIGHT - 1;
	y = -1;
	get_wall_step(g,&wall, dda, height);
	init_wall(p, dda, g, &wall);
	if (start < 0)
	{
		wall.tex_pos = (-start) * wall.step;  // COMPENSA O CLIPPING
		start = 0;
	}
    if (end >= HEIGHT)
        end = HEIGHT - 1;

    // Teto
    for (int y = 0; y < start; ++y)
        put_pixel(&g->bg, x, y, g->ceiling_color);

    // Parede
    for (int y = start; y <= end; ++y)
    {
         wall.texY = (int)wall.tex_pos;
        if ( wall.texY >= wall.texture->height) wall.texY = wall.texture->height - 1;  // seguro p/ não-potência de 2
        wall.tex_pos += wall.step;

        wall.color = get_pixel(wall.texture, wall.texX, wall.texY);
        if (dda->side == 1)
            wall.color = (wall.color >> 1) & 0x7F7F7F; // alternativa mais clara p/ escurecer
        put_pixel(&g->bg, x, y, wall.color);
    }

    // Chão
    for (int y = end + 1; y < HEIGHT; ++y)
        put_pixel(&g->bg, x, y, g->floor_color);
}

// void	draw_section(t_game *g, double perpWallDist, int x, t_img_data *wall)
// {
// 	int	start;
// 	int	end;
// 	int	height;
// 	int	y;

// 	if (perpWallDist <= 0.000001)
// 		perpWallDist = 0.000001;
// 	height = (int) (HEIGHT/ perpWallDist);
// 	start = -height / 2 + HEIGHT / 2;
// 	if (start < 0)
// 		start = 0;
// 	end = height / 2 + HEIGHT / 2;
// 	if (end >= HEIGHT)
// 		end = HEIGHT - 1;
// 	y = -1;
// 	while (++y < start)
// 		put_pixel(g->bg, x, y, g->ceiling_color);
// 	while(++y <= end)
// 		put_pixel(g->bg, x, y, get_pixel(wall, x,y));
// 	while(++y < HEIGHT)
// 		put_pixel(g->bg, x, y, g->floor_color);
// }

double	get_perp_dist(double hyp, double angle, double p_angle)
{
	return (hyp * cos(angle - p_angle));
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