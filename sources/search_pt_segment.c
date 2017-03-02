/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_pt_segment.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdrouet <cdrouet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/02 08:12:05 by cdrouet           #+#    #+#             */
/*   Updated: 2017/03/02 13:21:34 by cdrouet          ###   ########.fr       */
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

static t_pts	horizontal_search(t_all *all, double angle, double uncorrected_angle)
{
	t_pts	intersection;
	int		xa;
	int		ya;
	double	triangle_angle;

	triangle_angle = fabs(fabs(uncorrected_angle) - fabs(all->player->angle));
	intersection.y = ((int)(all->player->pos.y / 64) * 64) +
		((angle >= 0 && angle < 180) ?  -1 : 64);
	intersection.x = all->player->pos.x + ((all->player->pos.y - intersection.y)
		/ tan((angle * M_PI) / 180));
	ya = (angle >= 0 && angle < 180 ) ? -64 : 64;
	xa = 64 / tan((angle * M_PI) / 180);
	while (intersection.y >= 0 && intersection.y < (tab_len(all->map) * 64)
		&& intersection.x >= 0 && intersection.x < (int)(ft_strlen(all->map[0]) * 64)
		&& !verif_wall(intersection.x, intersection.y, all->map))
	{
		intersection.x += xa;
		intersection.y += ya;
	}
	return (intersection);
}

static t_pts	vertical_search(t_all *all, double angle, double uncorrected_angle)
{
	t_pts	intersection;
	int		xa;
	int		ya;
	double	triangle_angle;

	triangle_angle = fabs(fabs(uncorrected_angle) - fabs(all->player->angle));
	intersection.x = ((int)(all->player->pos.x / 64) * 64) +
		((angle >= 90 && angle < 270) ?  -1 : 64);
	intersection.y = all->player->pos.y + ((all->player->pos.x - intersection.x)
		/ tan((angle * M_PI) / 180));
	xa = (angle >= 90 && angle < 270 ) ? -64 : 64;
	ya = 64 * tan((angle * M_PI) / 180);
	while (intersection.y >= 0 && intersection.y < (tab_len(all->map) * 64)
		&& intersection.x >= 0 && intersection.x < (int)(ft_strlen(all->map[0]) * 64)
		&& !verif_wall(intersection.x, intersection.y, all->map))
	{
		intersection.x += xa;
		intersection.y += ya;
	}
	return (intersection);
}

t_pts			search_pts_in_space(t_all *all, double angle, double uncorrect)
{
	t_pts	a;
	t_pts	b;
	double	pa;
	double	pb;

//	printf("player.x %d %d ; player.y %d %d\n", all->player->pos.x, all->player->pos.x / 64,
//			all->player->pos.y, all->player->pos.y / 64);
//	printf("angle %f ; uncorrect %f\n", angle, uncorrect);
	if (angle != 180 && angle != 0)
		a = horizontal_search(all, angle, uncorrect);
	if (angle != 90 && angle != 270)
		b = vertical_search(all, angle, uncorrect);
	if (angle == 180  || angle == 0)
		return (b);
	if (angle == 270 || angle == 90)
		return (a);
	pa = abs(all->player->pos.x - a.x) / cos((angle * M_PI) / 180);
	pb = abs(all->player->pos.x - b.x) / cos((angle * M_PI) / 180);
//	printf("\na.x %d %d ; a.y %d %d\nb.x %d %d ; b.y %d %d\n", a.x, a.x / 64, a.y, a.y / 64, b.x, b.x / 64, b.y, b.y / 64);
//	printf("\npa %f ; pb %f\n", pa, pb);
	return ((pa > pb) ? b : a);
}
