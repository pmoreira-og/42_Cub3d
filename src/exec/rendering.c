#include "../../include/cub3d.h"


//? dir - fov/2 + x * step DIGITAL APPROACH
//? dir + fov/2 - (x + 0.5 ) * step MATH APPROACH
void	draw_map(t_game *g)
{
	t_point	p;
	double	angle;
	double	step;
	int		x;
	double	dist;

	p.x = g->player.pos_x / g->scale;
	p.y = g->player.pos_y / g->scale;
	angle = g->player.direction + deg2rad(FOV / 2);
	x = -1;
	dist = -1;
	step = deg2rad(FOV / (double) WIDTH);
	while (++x < WIDTH)
	{
		dist = collider_dda(p, angle - ((x + 0.5) * step), g, NULL);
		if (dist == -1)
			continue ;
		dist = get_perp_dist(dist, angle - ((x + 0.5) * step), g->player.direction);
		draw_section(g, dist * g->scale * 0.1, x);
	}
	mlx_put_image_to_window(g->mlx, g->win, g->bg->img, 0, 0);
}


//! ADAPT TO NEW WAY
// void	render_minimap(t_game *game)
// {
// 	t_point	a;
// 	double	angle;
// 	double	dist;
// 	// t_point	hit;

// 	dist = 0;
// 	a.x = game->player.pos_x;
// 	a.y = game->player.pos_y;
// 	angle = game->player.direction;
// 	while (1/* angle <= game->player.direction + 34 */)
// 	{
// 		dist = collider_angle(a, angle, WIDTH, game);
// 		// dist = collider_dda(a, angle, game, &hit);
	
// 		printf("[%f]dist:%f\n", angle, dist);
// 		if (dist != -1)
// 			draw(a, angle, WIDTH, game);
// 		angle++;
// 		break;
// 	}
// 	mlx_put_image_to_window(game->mlx, game->win, game->bg->img, 0, 0);
// }



int	render_map(t_game *game)
{

	move_handler(game);
	if (!has__moved(game))
		return (1);
	if (game->bg && !get_next_img(game))
		return (0);
	draw_map(game);
	// render_minimap(game);
	return (1);
}
