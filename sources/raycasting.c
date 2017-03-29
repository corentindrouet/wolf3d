/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdrouet <cdrouet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 11:28:47 by cdrouet           #+#    #+#             */
/*   Updated: 2017/03/29 14:11:33 by cdrouet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static int		choose_index(double angle, short wall_direction)
{
	if (wall_direction)
	{
		if (angle >= 0 && angle < 180)
			return (0);
		else
			return (1);
	}
	if (angle >= 90 && angle < 270)
		return (2);
	return (3);
}

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

static void		write_column(t_all *all, t_pts_dist dist, int x, int color)
{
	int		col_len;
	double	cam_proj_dist;
	int		corner_size;
	int		j;
	int		index;

	cam_proj_dist = round((all->mlx->win_size.x / 2) /
			all->precomputed->tan[(int)((ANGLE / 2) / all->index_divide)]);
	col_len = round((cam_proj_dist * BLOCK_SIZE) / dist.dist);
	col_len = (col_len / 2) * 2;
	corner_size = (all->mlx->win_size.y - col_len) / 2;
	j = 0;
	index = color;
	while (j < corner_size)
		write_img(x, j++, all->img, (int)0x00DBAE63);
	while (j < ((all->mlx->win_size.y - corner_size > all->mlx->win_size.y) ?
				all->mlx->win_size.y : (all->mlx->win_size.y - corner_size)))
	{
		if (!all->options.texture_problem && all->options.enable_texture)
			color = all->texture[index]->tab_bmp[
				index_map(col_len, corner_size, dist, j)];
		write_img(x, j++, all->img, color);
	}
	while (j < all->mlx->win_size.y)
		write_img(x, j++, all->img, (int)0x0051C228);
}

void			print_wall_to_img(t_all *all)
{
	double		angle;
	int			nb_col;
	double		d_angle;
	t_pts_dist	res;
	short		wall_direction;

	angle = all->player->angle + (ANGLE / 2)
		- ((all->player->angle >= 330) ? 360 : 0);
	nb_col = all->mlx->win_size.x;
	while (nb_col > 0)
	{
		d_angle = calcul_angle(all, angle, nb_col);
		res = search_pts_in_space(all, d_angle);
		wall_direction = (res.dist < 0) ? 1 : 0;
		if (res.dist < 0)
			res.dist *= -1;
		res.dist *= all->precomputed->cos[(int)fabs(angle_beta(
					d_angle, all->player) / all->index_divide)];
		write_column(all, res, all->mlx->win_size.x - nb_col,
					((!all->options.texture_problem
						&& all->options.enable_texture)
					? choose_index(d_angle, wall_direction)
					: choose_color(d_angle, wall_direction)));
		nb_col--;
	}
}
