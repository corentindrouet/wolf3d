/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   segment.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdrouet <cdrouet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/08 13:10:04 by cdrouet           #+#    #+#             */
/*   Updated: 2017/02/28 09:28:32 by cdrouet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	first_ca(t_pts d, t_pts start, t_pts stop, t_img *jpg)
{
	int		e;

	e = (d.x >= d.y) ? d.x : d.y;
	d.x *= 2;
	d.y *= 2;
	if (d.x >= d.y)
	{
		while (start.x != stop.x && write_img(start.y, start.x++, jpg))
			if ((e -= d.y) < 0)
			{
				start.y++;
				e += d.x;
			}
	}
	else
		while (start.y != stop.y && write_img(start.y++, start.x, jpg))
			if ((e -= d.x) < 0)
			{
				start.x++;
				e += d.y;
			}
}

void	last_ca(t_pts d, t_pts start, t_pts stop, t_img *jpg)
{
	int		e;

	e = (d.x >= -d.y) ? d.x : d.y;
	d.x *= 2;
	d.y *= 2;
	if (d.x >= -d.y)
	{
		while (start.x != stop.x && write_img(start.y, start.x++, jpg))
			if ((e += d.y) < 0)
			{
				start.y--;
				e += d.x;
			}
	}
	else
		while (start.y != stop.y && write_img(start.y--, start.x, jpg))
			if ((e += d.x) > 0)
			{
				start.x++;
				e += d.y;
			}
}

void	second_ca(t_pts d, t_pts start, t_pts stop, t_img *jpg)
{
	int		e;

	e = (-d.x >= d.y) ? d.x : d.y;
	d.x *= 2;
	d.y *= 2;
	if (-d.x >= d.y)
	{
		while (start.x != stop.x && write_img(start.y, start.x--, jpg))
			if ((e += d.y) >= 0)
			{
				start.y++;
				e += d.x;
			}
	}
	else
		while (start.y != stop.y && write_img(start.y++, start.x, jpg))
			if ((e += d.x) <= 0)
			{
				start.x--;
				e += d.y;
			}
}

void	third_ca(t_pts d, t_pts start, t_pts stop, t_img *jpg)
{
	int		e;

	e = (d.x <= d.y) ? d.x : d.y;
	d.x *= 2;
	d.y *= 2;
	if (d.x <= d.y)
	{
		while (start.x != stop.x && write_img(start.y, start.x--, jpg))
			if ((e -= d.y) >= 0)
			{
				start.y--;
				e += d.x;
			}
	}
	else
		while (start.y != stop.y && write_img(start.y--, start.x, jpg))
			if ((e -= d.x) >= 0)
			{
				start.x--;
				e += d.y;
			}
}

void	trace_segment(t_pts start, t_pts stop, t_img *jpg)
{
	t_pts	d;

	d.x = stop.x - start.x;
	d.y = stop.y - start.y;
	if (d.x > 0)
		d_x_pos(d, start, stop, jpg);
	else if (d.x < 0)
		d_x_neg(d, start, stop, jpg);
	else
	{
		if (d.y > 0)
			while (start.y != stop.y)
				write_img(start.y++, start.x, jpg);
		else if (d.y < 0)
			while (start.y != stop.y)
				write_img(start.y--, start.x, jpg);
	}
}
