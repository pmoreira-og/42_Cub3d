#include "../../include/cub3d.h"

// void	draw_section(t_game *g, double perpWallDist, int x)
// {
// 	 if (perpWallDist <= 0.000001) perpWallDist = 0.000001; // avoid div-by-zero

//     int lineHeight = (int)(HEIGHT / perpWallDist);

//     int drawStart = -lineHeight / 2 + HEIGHT / 2;
//     if (drawStart < 0) drawStart = 0;

//     int drawEnd = lineHeight / 2 + HEIGHT / 2;
//     if (drawEnd >= HEIGHT) drawEnd = HEIGHT - 1;

//     // optional: fill ceiling
//     for (int y = 0; y < drawStart; y++)
//         put_pixel(g->bg, x, y, 0x202020);

//     // wall slice
//     for (int y = drawStart; y <= drawEnd; y++)
//         put_pixel(g->bg, x, y, 0x00FF00);

//     // optional: fill floor
//     for (int y = drawEnd + 1; y < HEIGHT; y++)
//         put_pixel(g->bg, x, y, 0x404040);
// }
