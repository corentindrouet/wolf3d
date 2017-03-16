/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_pt_segment.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdrouet <cdrouet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/02 08:12:05 by cdrouet           #+#    #+#             */
/*   Updated: 2017/03/16 14:16:01 by cdrouet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include <stdio.h>

int					verif_wall(int x, int y, char **map)
{
	if ((y / BLOCK_SIZE) >= tab_len(map) || y < 0 ||
			(x / BLOCK_SIZE) >= (int)ft_strlen(map[0]) || x < 0)
		return (0);
	return (map[y / BLOCK_SIZE][x / BLOCK_SIZE] - '0');
}

static t_double_pts	horizontal_search(t_all *all, double angle)
{
	t_double_pts	pos;
	double			xa;
	double			ya;

	pos.y = ((int)(all->player->pos.y / BLOCK_SIZE) * BLOCK_SIZE) +
		((angle >= 0 && angle < 180) ? 0 : BLOCK_SIZE);
	pos.x = all->player->pos.x + ((all->player->pos.y - pos.y)
		/ tan(RAD(angle)));
	ya = (angle >= 0 && angle < 180) ? -BLOCK_SIZE : BLOCK_SIZE;
	xa = ((angle >= 180) ? -1 : 1) * (BLOCK_SIZE / tan(RAD(angle)));
	if (angle >= 0 && angle < 180)
		pos.y--;
	while (pos.y >= 0 && pos.y < (double)(tab_len(all->map) * BLOCK_SIZE)
		&& pos.x >= 0 && pos.x < (double)(ft_strlen(all->map[0]) * BLOCK_SIZE)
		&& !verif_wall(pos.x, pos.y, all->map))
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
		* tan(RAD(angle)));
	xa = (angle >= 90 && angle < 270) ? -BLOCK_SIZE : BLOCK_SIZE;
	ya = ((angle >= 90 && angle < 270) ? 1 : -1) *
			(BLOCK_SIZE * tan(RAD(angle)));
	if (angle >= 90 && angle < 270)
		pos.x--;
	while (pos.y >= 0 && pos.y < (double)(tab_len(all->map) * BLOCK_SIZE)
		&& pos.x >= 0 && pos.x < (double)(ft_strlen(all->map[0]) * BLOCK_SIZE)
		&& !verif_wall(pos.x, pos.y, all->map))
	{
		pos.x += xa;
		pos.y += ya;
	}
	return (pos);
}

double				search_pts_in_space(t_all *all, double angle)
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
	pb = hypot((double)all->player->pos.x - b.x, (double)all->player->pos.y - b.y);
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
