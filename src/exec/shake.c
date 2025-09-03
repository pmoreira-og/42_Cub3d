#include "../../include/cub3d.h"

void	init_bob_struct(t_game *g)
{
	g->player.bob.prev_x = g->player.pos_x / g->scale;
	g->player.bob.prev_y = g->player.pos_y / g->scale;
}

static double	get_dist(t_player *p)
{
	double	dx;
	double	dy;

	dx = p->pos_x - p->bob.prev_x;
	dy = p->pos_y - p->bob.prev_y;
	return (sqrt(dx * dx + dy * dy));
}

void	apply_bob_effect(t_player *p, t_game *g)
{
	double	dist;
	double	phase_step;

	dist = get_dist(p);
	if (g->sprint && !p->m_left && !p->m_right && p->m_forward)
	{
		p->bob.curr_amp += ((TARGET_AMP * 2) - p->bob.curr_amp) * SMOOTH;
		phase_step = dist * (2.0 * PI / (CYCLE_LENGTH * 1.33));
	}
	else
	{
		p->bob.curr_amp += (TARGET_AMP - p->bob.curr_amp) * SMOOTH;
		phase_step = dist * (2.0 * PI / CYCLE_LENGTH);
	}
	p->bob.phase += phase_step;
	if (p->bob.phase > 2.0 * PI)
		p->bob.phase -= 2.0 * PI;
	p->bob.cam_pitch = sin(p->bob.phase) * p->bob.curr_amp;
	p->bob.prev_x = p->pos_x;
	p->bob.prev_y = p->pos_y;
}
