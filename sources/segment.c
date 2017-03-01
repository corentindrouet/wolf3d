/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   segment.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdrouet <cdrouet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/08 13:10:04 by cdrouet           #+#    #+#             */
/*   Updated: 2017/03/01 11:14:27 by cdrouet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include <stdio.h>

t_pts	first_ca(t_pts d, t_pts start, t_pts stop, char **map)
{
	int		e;

	e = (d.x >= d.y) ? d.x : d.y;
	d.x *= 2;
	d.y *= 2;
	if (d.x >= d.y)
	{
		while (start.x != stop.x && !verif_wall(start.x++, start.y, map))
			if ((e -= d.y) < 0)
			{
				start.y++;
				e += d.x;
			}
	}
	else
		while (start.y != stop.y && !verif_wall(start.x, start.y++, map))
			if ((e -= d.x) < 0)
			{
				start.x++;
				e += d.y;
			}
	return (start);
}

t_pts	last_ca(t_pts d, t_pts start, t_pts stop, char **map)
{
	int		e;

	e = (d.x >= -d.y) ? d.x : d.y;
	d.x *= 2;
	d.y *= 2;
	if (d.x >= -d.y)
	{
		while (start.x != stop.x && !verif_wall(start.x++, start.y, map))
			if ((e += d.y) < 0)
			{
				start.y--;
				e += d.x;
			}
	}
	else
	{
		while (start.y != stop.y && !verif_wall(start.x, start.y--, map))
			if ((e += d.x) > 0)
			{
				start.x++;
				e += d.y;
			}
	}
	return (start);
}

t_pts	second_ca(t_pts d, t_pts start, t_pts stop, char **map)
{
	int		e;

	e = (-d.x >= d.y) ? d.x : d.y;
	d.x *= 2;
	d.y *= 2;
	if (-d.x >= d.y)
	{
		while (start.x != stop.x && !verif_wall(start.x--, start.y, map))
			if ((e += d.y) >= 0)
			{
				start.y++;
				e += d.x;
			}
	}
	else
		while (start.y != stop.y && !verif_wall(start.x, start.y++, map))
			if ((e += d.x) <= 0)
			{
				start.x--;
				e += d.y;
			}
	return (start);
}

t_pts	third_ca(t_pts d, t_pts start, t_pts stop, char **map)
{
	int		e;

	e = (d.x <= d.y) ? d.x : d.y;
	d.x *= 2;
	d.y *= 2;
	if (d.x <= d.y)
	{
		while (start.x != stop.x && !verif_wall(start.x--, start.y, map))
			if ((e -= d.y) >= 0)
			{
				start.y--;
				e += d.x;
			}
	}
	else
		while (start.y != stop.y && !verif_wall(start.x, start.y--, map))
			if ((e -= d.x) >= 0)
			{
				start.x--;
				e += d.y;
			}
	return (start);
}

t_pts	trace_segment(t_pts start, t_pts stop, char **map)
{
	t_pts	d;

	d.x = stop.x - start.x;
	d.y = stop.y - start.y;
	if (d.x > 0)
		d = d_x_pos(d, start, stop, map);
	else if (d.x < 0)
		d = d_x_neg(d, start, stop, map);
	else
	{
		if (d.y > 0)
			while (start.y != stop.y && !verif_wall(start.x, start.y, map))
				start.y++;
		else if (d.y < 0)
			while (start.y != stop.y && !verif_wall(start.x, start.y, map))
				start.y--;
		d = start;
	}
	return (d);
}
