#include "../../include/cub3d.h"

#define LEVELS 6  // número de níveis de luz (ajusta)

static const uint8_t bayer4[4][4] = {
    { 0,  8,  2, 10},
    {12,  4, 14,  6},
    { 3, 11,  1,  9},
    {15,  7, 13,  5}
};

// Função que já tinhas ou adaptas
// static float distance_light(float dist) {
//     // Exemplo simples (tweak constants)
//     float k1 = 0.10f, k2 = 0.04f;
//     float atten = 1.0f / (1.0f + k1*dist + k2*dist*dist);
//     if (atten > 1.0f) atten = 1.0f;
//     return atten;
// }

// Se já tiveres gravado distâncias por coluna, podes reaproveitar,
// ou armazenar um depth buffer (perpWallDist atribuído às linhas de parede;
// para chão/ceiling talvez recalcular ou ignorar).
void apply_dithering(t_img_data *img)
{
    // depth_buffer[y*width + x] = distância (para parede) ou estimada; se não tiver,
    // podes usar apenas luminância do pixel para quantização.
    for (int y = 0; y < HEIGHT; ++y) {
        for (int x = 0; x < WIDTH; ++x) {
            int c = get_pixel(img, x, y)/*  pixels[y*width + x] */;
            int r = (c >> 16) & 0xFF;
            int g = (c >> 8)  & 0xFF;
            int b = c & 0xFF;

            // Luminância aproximada (evitar float caro? pode usar ints)
            float lum = (0.2126f*r + 0.7152f*g + 0.0722f*b) / 255.0f;

            // // Combinar com luz por distância (opcional)
            // if (depth_buffer) {
            //     float dist = depth_buffer[y*width + x];
            //     if (dist > 0.0f) {
            //         float dl = distance_light(dist);
            //         // Exemplo: mistura lum original com atenuação
            //         lum *= dl;
            //     }
            // }

            if (lum < 0) lum = 0;
            if (lum > 1) lum = 1;

            float scaled = lum * (LEVELS - 1);

            int base = (int)scaled;
            float frac = scaled - base;

            float threshold = bayer4[y & 3][x & 3] / 16.0f;

            int level = base + (frac > threshold ? 1 : 0);
            if (level >= LEVELS) level = LEVELS - 1;

            float final_lum = level / (float)(LEVELS - 1);

            // Reaplica luminosidade aos canais (grayscale shading multiplicativo)
		    r = (int)(r * final_lum);
            g = (int)(g * final_lum);
            b = (int)(b * final_lum);

            // pixels[y*width + x] = (r << 16) | (g << 8) | b;
			put_pixel(img, x, y, get_color(r, g, b));
        }
    }
}

double	get_light(int y)
{
	double	light;
	double	step;

	light = 1;
	step = (2.0 / HEIGHT);
	if (y >= (HEIGHT / 2))
		y = HEIGHT - y;
	light -= y * step;
	if (light < 0.05)
		light = 0.05;
	// if ( light < 0.5)
	// 	light *= 0.15;
	// else
	// 	light = 1 - y * step;
	return (light);
}

int	apply_light(int color, double light)
{
	int	r;
	int	g;
	int	b;

	r = (((color >> 16 & 0xFF)) * light);
	g = (((color >> 8 & 0xFF)) * light);
	b = (((color & 0xFF)) * light);
	return (get_color(r, g, b));
}

int	get_color(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}