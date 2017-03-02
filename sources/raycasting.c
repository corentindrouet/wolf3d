/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdrouet <cdrouet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 11:28:47 by cdrouet           #+#    #+#             */
/*   Updated: 2017/03/02 13:21:34 by cdrouet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include <stdio.h>

static void		write_column(t_mlx *game, t_mlx_img *img, int dist, int x)
{
	int		i;
	int		col_len;
	double	cam_proj_dist;

	cam_proj_dist = (double)(game->win_size.x / 2) / tan((30 * M_PI) / 180);
	col_len = (cam_proj_dist * 64) / dist;
	i = 0;
	while (i < game->win_size.y)
	{
		if (i > ((game->win_size.y - col_len) / 2) &&
			i < (((game->win_size.y - col_len) / 2) + col_len))
			write_img(x, i, img, (int)0x0000FF00);
		i++;
	}
}

/*static t_pts	search_stop_pos(double angle, char **map, t_player *player, double uncorrected_angle)
{
	t_pts	ret;
	int		*calcul;
	int		*pos;

	calcul = ((angle < 45 || angle >= 315) || (angle >= 135 && angle < 225)) ?
		&(ret.y) : &(ret.x);
	pos = ((angle < 45 || angle >= 315) || (angle >= 135 && angle < 225)) ?
		&(ret.x) : &(ret.y);
	*calcul = (((angle < 45 || angle >= 315) || (angle >= 135 && angle < 225)) ?
			player->pos.y : player->pos.x) + (((uncorrected_angle > player->angle) ? -1 : +1) *
			(((double)(((angle < 45 || angle >= 315) || (angle >= 135 && angle < 225)) ?
			((ft_strlen(map[0]) * 64) - player->pos.x) :
			((tab_len(map) * 64) - player->pos.y)) /
			sin((double)((double)(180 - (double)(90 + (double)(fabs(uncorrected_angle) - fabs(player->angle)))) * M_PI) /
			180)) * sin((double)((double)(fabs(uncorrected_angle) - fabs(player->angle)) * M_PI) / 180)));
	if (angle < 45 || angle >= 315)
		*pos = ft_strlen(map[0]) * 64;
	else if ((angle >= 45 && angle < 225))
		*pos = 0;
	else if (angle >= 225 && angle < 315)
		*pos = tab_len(map) * 64;
//	printf("%d - %d - %d - %d - %f - %f - %f\n", ret.x, ret.y, *calcul, *pos, angle, uncorrected_angle, player->angle);
	return (ret);
}*/

static double	angle_beta(double angle, t_player *player)
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
	t_pts		stop;
	double		d_angle;
	double		uncorrected_angle;

	angle.x = all->player->angle + 30 - ((all->player->angle >= 330) ? 360 : 0);
	angle.y = all->player->angle - 30 + ((all->player->angle < 30) ? 360 : 0);
	nb_col = all->mlx->win_size.x;
	while (nb_col > 0)
	{
		d_angle = (double)angle.x - ((double)(60 / (double)all->mlx->win_size.x)
				* (double)((double)all->mlx->win_size.x - nb_col));
		uncorrected_angle = d_angle;
		if (d_angle < 0)
			d_angle = 360 + d_angle;
		stop = search_pts_in_space(all, d_angle, uncorrected_angle);
		write_column(all->mlx, img, hypot(stop.x - all->player->pos.x,
					stop.y - all->player->pos.y)
			* cos((angle_beta(d_angle, all->player) * M_PI) / 180), all->mlx->win_size.x - nb_col);
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
