/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdrouet <cdrouet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/29 13:15:25 by cdrouet           #+#    #+#             */
/*   Updated: 2017/03/29 13:27:26 by cdrouet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int		index_map(int col_len, int corner_size, t_pts_dist dist, int j)
{
	int	color;

	color = ((j - corner_size) * 100) / col_len;
	color = (BLOCK_SIZE * color) / 100;
	return ((color * BLOCK_SIZE) + ((int)dist.pt.x % BLOCK_SIZE));
}

double	calcul_angle(t_all *all, double angle, int nb_col)
{
	double	d_angle;

	d_angle = (double)angle
		- ((double)(ANGLE / (double)all->mlx->win_size.x)
				* (double)((double)all->mlx->win_size.x - nb_col));
	if (d_angle < 0)
		d_angle = 360 + d_angle;
	return (d_angle);
}
