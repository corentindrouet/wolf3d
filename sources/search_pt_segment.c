/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_pt_segment.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdrouet <cdrouet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/02 08:12:05 by cdrouet           #+#    #+#             */
/*   Updated: 2017/03/03 11:45:18 by cdrouet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include <stdio.h>

int				verif_wall(int x, int y, char **map)
{
	if ((y / 64) >= tab_len(map) || y < 0 ||
			(x / 64) >= (int)ft_strlen(map[0]) || x < 0)
		return (0);
	return (map[y / 64][x / 64] - '0');
}

static t_pts	horizontal_search(t_all *all, double angle)
{
	t_pts	intersection;
	int		xa;
	int		ya;

	intersection.y = ((int)(all->player->pos.y / 64) * 64) +
		((angle >= 0 && angle < 180) ?  -1 : 64);
	intersection.x = round(all->player->pos.x + ((all->player->pos.y - intersection.y)
		/ tan((angle * M_PI) / 180)));
	ya = (angle >= 0 && angle < 180 ) ? -64 : 64;
	xa = round(((angle >= 180) ? -1 : 1) * (64 / tan((angle * M_PI) / 180)));
	while (intersection.y >= 0 && intersection.y < (tab_len(all->map) * 64)
		&& intersection.x >= 0 && intersection.x < (int)(ft_strlen(all->map[0]) * 64)
		&& !verif_wall(intersection.x, intersection.y, all->map))
	{
		intersection.x += xa;
		intersection.y += ya;
	}
	return (intersection);
}

static t_pts	vertical_search(t_all *all, double angle)
{
	t_pts	intersection;
	int		xa;
	int		ya;

	intersection.x = ((int)(all->player->pos.x / 64) * 64) +
		((angle >= 90 && angle < 270) ?  -1 : 64);
	intersection.y = round(all->player->pos.y + ((all->player->pos.x - intersection.x)
		* tan((angle * M_PI) / 180)));
	xa = (angle >= 90 && angle < 270 ) ? -64 : 64;
	ya = round(((angle >= 90 && angle < 270) ? 1 : -1) * (64 * tan((angle * M_PI) / 180)));
	while (intersection.y >= 0 && intersection.y < (tab_len(all->map) * 64)
		&& intersection.x >= 0 && intersection.x < (int)(ft_strlen(all->map[0]) * 64)
		&& !verif_wall(intersection.x, intersection.y, all->map))
	{
		intersection.x += xa;
		intersection.y += ya;
	}
	return (intersection);
}

double			search_pts_in_space(t_all *all, double angle)
{
	t_pts	a;
	t_pts	b;
	double	pa;
	double	pb;

	pa = 0;
	pb = 0;
//	if (angle != 180 && angle != 0)
//	{
		a = horizontal_search(all, angle);
		pa = hypot(all->player->pos.x - a.x, all->player->pos.y - a.y);
//	}
//	if (angle != 90 && angle != 270)
//	{
		b = vertical_search(all, angle);
		pb = hypot(all->player->pos.x - b.x, all->player->pos.y - b.y);
//	}
	printf("pa %f a.x %d a.y %d pb %f b.x %d b.y %d", pa, a.x, a.y, pb, b.x, b.y);
	if (angle == 180  || angle == 0 || a.x < 0 || a.y < 0
			|| a.x >= (int)(ft_strlen(all->map[0]) * 64)
			|| a.y >= (tab_len(all->map) * 64))
		return (pb);
	if (angle == 270 || angle == 90 || b.x < 0 || b.y < 0
			|| b.x >= (int)(ft_strlen(all->map[0]) * 64)
			|| b.y >= (tab_len(all->map) * 64))
		return (-pa);
	return ((pa > pb) ? pb : -pa);
}
