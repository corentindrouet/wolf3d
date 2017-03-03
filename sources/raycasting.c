/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdrouet <cdrouet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 11:28:47 by cdrouet           #+#    #+#             */
/*   Updated: 2017/03/03 14:57:45 by cdrouet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include <stdio.h>

static int		choose_color(double angle, short wall_direction)
{
	if (wall_direction)
	{
		if (angle >= 0 && angle < 180)
			return ((int)0x000000FF);
		else
			return ((int)0x0000FF00);
	}
	if (angle >= 90 && angle < 270)
		return ((int)0x00FF0000);
	return ((int)0x00FFFFFF);
}

static void		write_column(t_all *all, int dist, int x, int color)
{
	int		i;
	int		col_len;
	double	cam_proj_dist;
	int		n;

	cam_proj_dist = round((all->mlx->win_size.x / 2) / tan(RAD(30)));
	col_len = round((cam_proj_dist * BLOCK_SIZE) / dist);
	i = all->mlx->win_size.y / 2;
	n = i - (col_len / 2);
	while (i > n)
		write_img(x, i--, all->img, color);
	while (i >= 0)
		write_img(x, i--, all->img, (int)0x00DBAE63);
	i = all->mlx->win_size.y / 2;
	n = i + (col_len / 2);
	while (i < n)
		write_img(x, i++, all->img, color);
	while (i < all->mlx->win_size.y)
		write_img(x, i++, all->img, (int)0x0051C228);
}

double			angle_beta(double angle, t_player *player)
{
	if (player->angle < 29 && angle >= 329)
		return (angle - (player->angle + 360));
	if (player->angle > 329 && angle < 29)
		angle += player->angle;
	return (angle - player->angle);
}

void			print_wall_to_img(t_all *all)
{
	double		angle;
	int			nb_col;
	double		d_angle;
	double		res;
	short		wall_direction;

	angle = all->player->angle + 30 - ((all->player->angle >= 330) ? 360 : 0);
	nb_col = all->mlx->win_size.x;
	while (nb_col > 0)
	{
		d_angle = (double)angle - ((double)(60 / (double)all->mlx->win_size.x)
				* (double)((double)all->mlx->win_size.x - nb_col));
		if (d_angle < 0)
			d_angle = 360 + d_angle;
		res = search_pts_in_space(all, d_angle);
		wall_direction = (res < 0) ? 1 : 0;
		if (res < 0)
			res *= -1;
		write_column(all, round(res * cos(RAD(angle_beta(d_angle,
					all->player)))), all->mlx->win_size.x - nb_col,
					choose_color(d_angle, wall_direction));
		nb_col--;
	}
}

void			raycast(t_all *all_structs)
{
	all_structs->img = new_image(all_structs->mlx->mlx,
			all_structs->mlx->win_size.x,
			all_structs->mlx->win_size.y);
	print_wall_to_img(all_structs);
}
