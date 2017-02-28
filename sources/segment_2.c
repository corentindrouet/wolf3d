/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   segment_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdrouet <cdrouet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/12 14:17:02 by cdrouet           #+#    #+#             */
/*   Updated: 2016/02/12 14:22:50 by cdrouet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	d_x_pos(t_pts d, t_pts start, t_pts stop, t_img *jpg)
{
	if (d.y > 0)
		first_ca(d, start, stop, jpg);
	else if (d.y < 0)
		last_ca(d, start, stop, jpg);
	else
		while (start.x != stop.x)
			write_img(start.y, start.x++, jpg);
}

void	d_x_neg(t_pts d, t_pts start, t_pts stop, t_img *jpg)
{
	if (d.y > 0)
		second_ca(d, start, stop, jpg);
	else if (d.y < 0)
		third_ca(d, start, stop, jpg);
	else
		while (start.x != stop.x)
			write_img(start.y, start.x--, jpg);
}
