/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   segment_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdrouet <cdrouet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/12 14:17:02 by cdrouet           #+#    #+#             */
/*   Updated: 2017/02/28 13:41:46 by cdrouet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		verif_wall(int x, int y, char **map)
{
	return (map[pt.y / 64][pt.x / 64] - '0');
}

t_pts	d_x_pos(t_pts d, t_pts start, t_pts stop, char **map)
{
	if (d.y > 0)
		return first_ca(d, start, stop, map);
	else if (d.y < 0)
		return last_ca(d, start, stop, map);
	else
		while (start.x != stop.x && !verif_wall(start.x, start.y, map))
			start.x++;
	return start;
}

t_pts	d_x_neg(t_pts d, t_pts start, t_pts stop, char **map)
{
	if (d.y > 0)
		return second_ca(d, start, stop, map);
	else if (d.y < 0)
		return third_ca(d, start, stop, map);
	else
		while (start.x != stop.x && !verif_wall(start.x, start.y, map))
			start.x--;
	return start;
}
