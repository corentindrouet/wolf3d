/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_pt_segment.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdrouet <cdrouet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/02 08:12:05 by cdrouet           #+#    #+#             */
/*   Updated: 2017/03/29 12:52:33 by cdrouet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static t_double_pts	horizontal_search(t_all *all, double angle)
{
	t_double_pts	pos;
	double			xa;
	double			ya;

	pos.y = ((int)(all->player->pos.y / BLOCK_SIZE) * BLOCK_SIZE) +
		((angle >= 0 && angle < 180) ? 0 : BLOCK_SIZE);
	pos.x = all->player->pos.x + ((all->player->pos.y - pos.y)
		/ all->precomputed->tan[(int)(angle / all->index_divide)]);
	ya = (angle >= 0 && angle < 180) ? -BLOCK_SIZE : BLOCK_SIZE;
	xa = ((angle >= 180) ? -1 : 1) * (BLOCK_SIZE /
			all->precomputed->tan[(int)(angle / all->index_divide)]);
	if (angle >= 0 && angle < 180)
		pos.y--;
	while (pos.y >= 0 && pos.y < (double)(all->map.size.y)
		&& pos.x >= 0 && pos.x < (double)(all->map.size.x)
		&& !verif_wall(pos.x, pos.y, &(all->map)))
	{
		pos.x += xa;
		pos.y += ya;
	}
	return (pos);
}

static t_double_pts	vertical_search(t_all *all, double angle)
{
	t_double_pts	pos;
	double			xa;
	double			ya;

	pos.x = ((int)(all->player->pos.x / BLOCK_SIZE) * BLOCK_SIZE) +
		((angle >= 90 && angle < 270) ? 0 : BLOCK_SIZE);
	pos.y = all->player->pos.y + ((all->player->pos.x - pos.x)
		* all->precomputed->tan[(int)(angle / all->index_divide)]);
	xa = (angle >= 90 && angle < 270) ? -BLOCK_SIZE : BLOCK_SIZE;
	ya = ((angle >= 90 && angle < 270) ? 1 : -1) *
			(BLOCK_SIZE *
			all->precomputed->tan[(int)(angle / all->index_divide)]);
	if (angle >= 90 && angle < 270)
		pos.x--;
	while (pos.y >= 0 && pos.y < (double)(all->map.size.y)
		&& pos.x >= 0 && pos.x < (double)(all->map.size.x)
		&& !verif_wall(pos.x, pos.y, &(all->map)))
	{
		pos.x += xa;
		pos.y += ya;
	}
	return (pos);
}

static t_double_pts	search_pt(double *p, t_all *all, double angle,
		t_double_pts (*f)(t_all *, double))
{
	t_double_pts	pt;
	double			tmp;

	pt = f(all, angle);
	(*p) = fabs(fabs(all->player->pos.y - pt.y) /
			all->precomputed->sin[(int)(angle / all->index_divide)]);
	if (!all->precomputed->sin[(int)(angle / all->index_divide)])
		(*p) = 0;
	tmp = fabs(fabs(all->player->pos.x - pt.x) /
			all->precomputed->cos[(int)(angle / all->index_divide)]);
	if ((tmp && tmp < (*p)) || !(*p))
		(*p) = tmp;
	return (pt);
}

static void			adjust_values(t_pts_dist *a, t_pts_dist *b, double angle)
{
	b->pt.x += b->pt.y;
	b->pt.y = b->pt.x - b->pt.y;
	b->pt.x = b->pt.x - b->pt.y;
	if (angle >= 90 && angle < 270)
		b->pt.x = (((int)b->pt.x / BLOCK_SIZE) * BLOCK_SIZE)
			+ (BLOCK_SIZE - ((int)b->pt.x % BLOCK_SIZE));
	if (angle >= 180)
		a->pt.x = (((int)a->pt.x / BLOCK_SIZE) * BLOCK_SIZE)
			+ (BLOCK_SIZE - ((int)a->pt.x % BLOCK_SIZE));
}

t_pts_dist			search_pts_in_space(t_all *all, double angle)
{
	t_pts_dist	a;
	t_pts_dist	b;

	a.dist = DBL_MAX;
	b.dist = DBL_MAX;
	if (angle != 180 && angle != 0)
		a.pt = search_pt(&(a.dist), all, angle, horizontal_search);
	if (angle != 270 && angle != 90)
		b.pt = search_pt(&(b.dist), all, angle, vertical_search);
	adjust_values(&a, &b, angle);
	if (angle == 180 || angle == 0 || a.pt.x < 0 || a.pt.y < 0
			|| a.pt.x >= (double)all->map.size.x
			|| a.pt.y >= (double)all->map.size.y
			|| a.dist == DBL_MAX)
		return (b);
	a.dist = -a.dist;
	if (angle == 270 || angle == 90 || b.pt.x < 0 || b.pt.y < 0
			|| b.pt.y >= (double)all->map.size.x
			|| b.pt.x >= (double)all->map.size.y
			|| b.dist == DBL_MAX)
		return (a);
	return ((-a.dist > b.dist) ? b : a);
}
