#include "../../include/cub3d.h"

// void	draw_map(t_game *game)
// {
// 	t_point	a;
// 	double	angle;
// 	double	dist;
// 	t_point	hit;

// 	dist = 0;
// 	a.x = game->player.pos_x;
// 	a.y = game->player.pos_y;
// 	angle = game->player.direction - 90;
// 	while (angle <= game->player.direction + 90)
// 	{
// 		dist = collider_dda(a, angle, game, &hit);
// 		if (dist == -1)
// 			continue ;
// 		draw_section(game, dist, (int) angle);
// 		angle++;
// 	}
// 	mlx_put_image_to_window(game->mlx, game->win, game->bg->img, 0, 0);
// }

#ifndef FOV_DEG
# define FOV_DEG 60.0   // typical FOV
#endif

static inline double deg2rad(double deg) {
    return deg * PI / 180.0;
}

static inline double normalize_deg(double deg) {
    while (deg < 0.0)   deg += 360.0;
    while (deg >= 360.0) deg -= 360.0;
    return deg;
}

void draw_section(t_game *g, double perpWallDist, int x)
{
    // if (perpWallDist <= 1e-6) perpWallDist = 1e-6; // avoid div-by-zero

    int lineHeight = (int)(HEIGHT / perpWallDist);

    int drawStart = -lineHeight / 2 + HEIGHT / 2;
    if (drawStart < 0) drawStart = 0;

    int drawEnd = lineHeight / 2 + HEIGHT / 2;
    if (drawEnd >= HEIGHT) drawEnd = HEIGHT - 1;

    // ceiling
    for (int y = 0; y < drawStart; y++)
        put_pixel(g->bg, x, y, 0x202020);

    // wall slice
    for (int y = drawStart; y <= drawEnd; y++)
        put_pixel(g->bg, x, y, 0x00FF00);

    // floor
    for (int y = drawEnd + 1; y < HEIGHT; y++)
        put_pixel(g->bg, x, y, 0x404040);
}

// Cast one ray per screen column and draw that column.
void draw_map(t_game *game)
{
    t_point a;
    t_point hit;

    a.x = game->player.pos_x;
    a.y = game->player.pos_y;

    // Map FOV across the screen columns
    const double half_fov = FOV_DEG * 0.5;
    const double start_angle = game->player.direction - half_fov;
    const double step = FOV_DEG / (double)WIDTH;

    // Optional: clear background first (one pass)
    for (int x = 0; x < WIDTH; x++) {
        for (int y = 0; y < HEIGHT; y++) {
            put_pixel(game->bg, x, y, (y < HEIGHT/2) ? 0x202020 : 0x404040);
        }
    }

	printf("dist:%f\n", collider_angle(a, game->player.direction, WIDTH, game));
	printf("dist:%f\n", collider_dda(a, game->player.direction, game, &hit));

    for (double x = 0; x < WIDTH; x += 0.5) {
        double ray_angle = start_angle + x * step;

        // If your collider_dda expects angles in [0,360), normalize:
        double dda_angle = normalize_deg(ray_angle);

        double dist = collider_angle(a, dda_angle, WIDTH, game);
        if (dist < 0) {
            // No hit: skip wall slice (background already drawn)
            continue;
        }

        // Perpendicular distance correction to avoid fisheye
        double angle_diff = ray_angle - game->player.direction;
        double perp = dist * cos(deg2rad(angle_diff));

        // If your collider_dda already returns perpendicular distance,
        // use 'dist' directly instead of 'perp'.
        draw_section(game, perp, x);
    }

    mlx_put_image_to_window(game->mlx, game->win, game->bg->img, 0, 0);
}
void	render_minimap(t_game *game)
{
	t_point	a;
	double	angle;
	double	dist;
	// t_point	hit;

	dist = 0;
	a.x = game->player.pos_x;
	a.y = game->player.pos_y;
	angle = game->player.direction;
	while (1/* angle <= game->player.direction + 34 */)
	{
		dist = collider_angle(a, angle, WIDTH, game);
		// dist = collider_dda(a, angle, game, &hit);
	
		printf("[%f]dist:%f\n", angle, dist);
		if (dist != -1)
			draw(a, angle, WIDTH, game);
		angle++;
		break;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->bg->img, 0, 0);
}


void	put_grid(t_game *g)
{
	char	*texture_data;
	int		i;

	texture_data = get_sprite_data(g, GRID);
	i = -1;
	// while (texture_data[++i])
	// {
		
	// }
	
	// mlx_put_image_to_window(g->mlx, g->win, img, 0, HEIGHT * 0.8);

}

// void	put_grid(t_game *g)
// {
// 	int	i,j;

// 	i = HEIGHT * 0.8;
// 	while(i < HEIGHT)
// 	{
// 		j = -1;
// 		while (++j < WIDTH * 0.20)
// 		{
// 			put_pixel(g->bg, j, i, 0x00FF00);
// 		}
// 		i++;
// 	}
// }

int	render_map(t_game *game)
{

	move_handler(game);
	if (!is_moved(game))
		return (1);
	if (game->bg && !get_next_img(game))
		return (0);
	draw_map(game);
	// render_minimap(game);
	// put_grid(game);
	return (1);
}
