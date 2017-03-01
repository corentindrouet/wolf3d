/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdrouet <cdrouet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 11:28:47 by cdrouet           #+#    #+#             */
/*   Updated: 2017/03/01 11:22:30 by cdrouet          ###   ########.fr       */
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
//	printf("dist = %d ; col_len = %d\n", dist, col_len);
	i = 0;
	while (i < game->win_size.y)
	{
		if (i > ((game->win_size.y - col_len) / 2) &&
			i < (((game->win_size.y - col_len) / 2) + col_len))
			write_img(x, i, img, (int)0x0000FF00);
		i++;
	}
}

static t_pts	search_stop_pos(double angle, char **map, t_player *player)
{
	t_pts	ret;
	int		*calcul;
	int		*pos;

	calcul = ((angle < 45 || angle >= 315) || (angle >= 135 && angle < 225)) ?
		&(ret.y) : &(ret.x);
	pos = ((angle < 45 || angle >= 315) || (angle >= 135 && angle < 225)) ?
		&(ret.x) : &(ret.y);
	*calcul = (((angle < 45 || angle >= 315) || (angle >= 135 && angle < 225)) ?
			player->pos.y : player->pos.x) +
			(((((angle < 45 || angle >= 315) || (angle >= 135 && angle < 225)) ?
			(((ft_strlen(map[0]) - 1) * 64) - player->pos.y) :
			(((tab_len(map) - 1) * 64) - player->pos.x)) /
			sin((double)((double)(180 - (double)(90 + (double)angle)) * M_PI) / 180)) *
			sin((double)((double)angle * M_PI) / 180));
	if (angle < 45 || angle >= 315)
		*pos = (ft_strlen(map[0]) - 1) * 64;
	else if ((angle >= 45 && angle < 225))
		*pos = 0;
	else if (angle >= 225 && angle < 315)
		*pos = (tab_len(map) - 1) * 64;
	return (ret);
}

static void		print_wall_to_img(t_mlx_img *img, char **map, t_player *player,
		t_mlx *game)
{
	t_pts		angle;
	int			nb_col;
	t_pts		stop;
	double		d_angle;

	angle.x = player->angle + 30 - ((player->angle >= 330) ? 360 : 0);
	angle.y = player->angle - 30 + ((player->angle < 30) ? 360 : 0);
	nb_col = game->win_size.x;
	while (nb_col > 0)
	{
		d_angle = (double)angle.x - ((double)(60 / (double)game->win_size.x) *
				(double)((double)game->win_size.x - nb_col));
		if (d_angle < 0)
			d_angle = 360 + d_angle;
		stop = search_stop_pos(d_angle, map, player);
//		printf("stop.x %d ; stop.y %d ; ", stop.x, stop.y);
		stop = trace_segment(player->pos, stop, map);
//		printf("stop.x %d ; stop.y %d ; ", stop.x / 64, stop.y / 64);
		write_column(game, img, hypot(stop.x - player->pos.x, stop.y - player->pos.y) *
					cos((double)((double)d_angle * M_PI) / 180), game->win_size.x - nb_col);
		nb_col--;
	}
}

int		tab_len(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

t_mlx_img		*raycast(t_mlx *game, char **map, t_player *player)
{
	t_mlx_img	*img;

	img = new_image(game->mlx, game->win_size.x, game->win_size.y);
	print_wall_to_img(img, map, player, game);
	return (img);
}
