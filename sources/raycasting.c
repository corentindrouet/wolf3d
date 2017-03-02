/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdrouet <cdrouet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 11:28:47 by cdrouet           #+#    #+#             */
/*   Updated: 2017/03/02 16:17:15 by cdrouet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void		write_column(t_mlx *game, t_mlx_img *img, double dist, int x)
{
	int		i;
	int		col_len;
	double	cam_proj_dist;
	int		n;

	cam_proj_dist = (double)(game->win_size.x / 2) / tan((30 * M_PI) / 180);
	col_len = (int)((cam_proj_dist * 64) / dist);
	i = game->win_size.y / 2;
	n = i - (col_len / 2);
	while (i > n)
		write_img(x, i--, img, (int)0x0000FF00);
	i = game->win_size.y / 2;
	n = i + (col_len / 2);
	while (i < n)
		write_img(x, i++, img, (int)0x0000FF00);
}

double			angle_beta(double angle, t_player *player)
{
	if (player->angle <= 29 && angle >= 329)
		return (angle - (player->angle + 360));
	if (player->angle > 329 && angle < 30)
		angle += player->angle;
	return (angle - player->angle);
}

void			print_wall_to_img(t_mlx_img *img, t_all *all)
{
	t_pts		angle;
	int			nb_col;
	double		d_angle;
	double		res;

	angle.x = all->player->angle + 30 - ((all->player->angle >= 330) ? 360 : 0);
	angle.y = all->player->angle - 30 + ((all->player->angle < 30) ? 360 : 0);
	nb_col = all->mlx->win_size.x;
	while (nb_col > 0)
	{
		d_angle = (double)angle.x - ((double)(60 / (double)all->mlx->win_size.x)
				* (double)((double)all->mlx->win_size.x - nb_col));
		if (d_angle < 0)
			d_angle = 360 + d_angle;
		res = search_pts_in_space(all, d_angle);
		write_column(all->mlx, img, res * cos((angle_beta(d_angle, all->player)
			* M_PI) / 180), all->mlx->win_size.x - nb_col);
		nb_col--;
	}
}

int				tab_len(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

t_mlx_img		*raycast(t_all *all_structs)
{
	t_mlx_img	*img;

	img = new_image(all_structs->mlx->mlx,
			all_structs->mlx->win_size.x,
			all_structs->mlx->win_size.y);
	print_wall_to_img(img, all_structs);
	return (img);
}
