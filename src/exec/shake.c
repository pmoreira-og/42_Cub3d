#include "../../include/cub3d.h"

void	init_bob_struct(t_game *g)
{
	g->player.bob.prev.x = g->player.pos.x;
	g->player.bob.prev.y = g->player.pos.y;
	g->move_speed = MOVESPEED;
	g->rot_speed = ROTSPEED;
}

static double	get_dist(t_player *p)
{
	double	dx;
	double	dy;

	dx = p->pos.x - p->bob.prev.x;
	dy = p->pos.y - p->bob.prev.y;
	return (sqrt(dx * dx + dy * dy));
}

void	apply_bob_effect(t_player *p, t_game *g)
{
	double	dist;
	double	phase_step;

	dist = get_dist(p);
	if (g->player.act.sprint && !p->act.m_left \
&& !p->act.m_right && p->act.m_forward)
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
	p->bob.prev.x = p->pos.x;
	p->bob.prev.y = p->pos.y;
}
