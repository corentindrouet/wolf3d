/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_pt_segment.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdrouet <cdrouet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/02 08:12:05 by cdrouet           #+#    #+#             */
/*   Updated: 2017/03/03 15:08:02 by cdrouet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include <stdio.h>

int				verif_wall(int x, int y, char **map)
{
	if ((y / BLOCK_SIZE) >= tab_len(map) || y < 0 ||
			(x / BLOCK_SIZE) >= (int)ft_strlen(map[0]) || x < 0)
		return (0);
	return (map[y / BLOCK_SIZE][x / BLOCK_SIZE] - '0');
}

static t_double_pts	horizontal_search(t_all *all, double angle)
{
	t_double_pts		pos;
	double		xa;
	double		ya;
	double	tmpx;
	double	tmpy;

	tmpy = ((int)(all->player->pos.y / BLOCK_SIZE) * BLOCK_SIZE) +
		((angle >= 0 && angle < 180) ? -1 : BLOCK_SIZE);
	tmpx = all->player->pos.x + (all->player->pos.y - tmpy)
		/ tan(RAD(angle));
	ya = (angle >= 0 && angle < 180) ? -BLOCK_SIZE : BLOCK_SIZE;
	xa = ((angle >= 180) ? -1 : 1) * (BLOCK_SIZE / tan(RAD(angle)));
	while (tmpy >= 0 && tmpy < (tab_len(all->map) * BLOCK_SIZE)
		&& tmpx >= 0 && tmpx < (int)(ft_strlen(all->map[0]) * BLOCK_SIZE)
		&& !verif_wall(tmpx, tmpy, all->map))
	{
		tmpx += xa;
		tmpy += ya;
	}
	pos.x = tmpx;
	pos.y = tmpy;
	return (pos);
}

static t_double_pts	vertical_search(t_all *all, double angle)
{
	t_double_pts		pos;
	double		xa;
	double		ya;
	double	tmpx;
	double	tmpy;

	tmpx = ((int)(all->player->pos.x / BLOCK_SIZE) * BLOCK_SIZE) +
		((angle >= 90 && angle < 270) ? -1 : BLOCK_SIZE);
	tmpy = all->player->pos.y + (all->player->pos.x - tmpx)
		* tan(RAD(angle));
	xa = (angle >= 90 && angle < 270) ? -BLOCK_SIZE : BLOCK_SIZE;
	ya = ((angle >= 90 && angle < 270) ? 1 : -1) *
			(BLOCK_SIZE * tan(RAD(angle)));
	while (tmpy >= 0 && tmpy < (tab_len(all->map) * BLOCK_SIZE)
		&& tmpx >= 0 && tmpx < (int)(ft_strlen(all->map[0]) * BLOCK_SIZE)
		&& !verif_wall(tmpx, tmpy, all->map))
	{
		tmpx += xa;
		tmpy += ya;
	}
	pos.x = tmpx;
	pos.y = tmpy;
	return (pos);
}

double			search_pts_in_space(t_all *all, double angle)
{
	t_double_pts	a;
	t_double_pts	b;
	double	pa;
	double	pb;

	pa = 0;
	pb = 0;
	a = horizontal_search(all, angle);
	pa = hypot((double)all->player->pos.x - a.x, (double)all->player->pos.y - a.y);
	b = vertical_search(all, angle);
	pb = hypot(all->player->pos.x - b.x, all->player->pos.y - b.y);
	if (angle == 180 || angle == 0 || a.x < 0 || a.y < 0
			|| a.x >= (double)(ft_strlen(all->map[0]) * BLOCK_SIZE)
			|| a.y >= (double)(tab_len(all->map) * BLOCK_SIZE))
		return (pb);
	if (angle == 270 || angle == 90 || b.x < 0 || b.y < 0
			|| b.x >= (double)(ft_strlen(all->map[0]) * BLOCK_SIZE)
			|| b.y >= (double)(tab_len(all->map) * BLOCK_SIZE))
		return (-pa);
	return ((pa > pb) ? pb : -pa);
}
