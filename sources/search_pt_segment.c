/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_pt_segment.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdrouet <cdrouet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/02 08:12:05 by cdrouet           #+#    #+#             */
/*   Updated: 2017/03/21 09:28:45 by cdrouet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include <stdio.h>

int					verif_wall(int x, int y, t_map *map)
{
	if (y >= (int)map->size.y || y < 0 ||
			x >= (int)map->size.x || x < 0)
		return (0);
	return (map->map[y / BLOCK_SIZE][x / BLOCK_SIZE] - '0');
}

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
	if (angle == 0)
		printf("p %f tmp %f\n", (*p), tmp);
	if ((tmp < (*p) && tmp) || !(*p))
		(*p) = tmp;
	return (pt);
}

double				search_pts_in_space(t_all *all, double angle)
{
	t_double_pts	a;
	t_double_pts	b;
	double			pa;
	double			pb;

	pa = DBL_MAX;
	pb = DBL_MAX;
	if (angle != 180 && angle != 0)
		a = search_pt(&pa, all, angle, horizontal_search);
	if (angle != 270 && angle != 90)
		b = search_pt(&pb, all, angle, vertical_search);
	if (angle == 180 || angle == 0 || a.x < 0 || a.y < 0
			|| a.x >= (double)all->map.size.x
			|| a.y >= (double)all->map.size.y
			|| pa == DBL_MAX)
		return (pb);
	if (angle == 270 || angle == 90 || b.x < 0 || b.y < 0
			|| b.x >= (double)all->map.size.x
			|| b.y >= (double)all->map.size.y
			|| pb == DBL_MAX)
		return (-pa);
	return ((pa > pb) ? pb : -pa);
}
