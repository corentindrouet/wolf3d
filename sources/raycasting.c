/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdrouet <cdrouet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 11:28:47 by cdrouet           #+#    #+#             */
/*   Updated: 2017/02/28 14:04:38 by cdrouet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void		write_column(t_mlx *game, t_mlx_img *img, t_pts start, t_pts stop)
{
	int	i;

	i = 0;
	while (i < game->win_size.y)
	{

	}
}

static int		tab_len(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

static t_pts	search_stop_pos(double angle, char **map, t_player *player)
{
	t_pts	ret;
	int		*calcul;
	int		*pos;

	calcul = ((angle < 45 && angle >= 315) || (angle >= 135 && angle < 225)) ?
		&(ret.y) : &(ret.x);
	pos = ((angle < 45 && angle >= 315) || (angle >= 135 && angle < 225)) ?
		&(ret.x) : &(ret.y);
	*calcul = (((angle < 45 && angle >= 315) || (angle >= 135 && angle < 225)) ?
			player->pos.y : player->pos.x) +
			(((((angle < 45 && angle >= 315) || (angle >= 135 && angle < 225)) ?
			((ft_strlen(map[0]) * 64) - player->pos.y) :
			((tab_len(map) * 64) - player->pos.x)) /
			sin(((180 - (90 + angle)) * M_PI) / 180)) *
			sin((angle * M_PI) / 180));
	if (angle < 45 && angle >= 315)
		*pos = ft_strlen(map[0]) * 64;
	else if ((angle >= 45 && angle < 225))
		*pos = 0;
	else if (angle >= 225 && angle < 315)
		*pos = tab_len(map) * 64;
	return (ret);
}

static void		print_wall_to_img(t_mlx_img *img, char **map, t_player *player,
		t_mlx *game)
{
	t_pts		angle;
	double		res;
	int			nb_col;
	t_pts		stop;
	double		d_angle;

	angle.x = player.angle + 30 - (player.angle >= 330) ? 360 : 0;
	angle.y = player.angle - 30 + (player.angle < 30) ? 360 : 0;
	nb_col = game->win_size.x;
	while (nb_col > 0)
	{
		d_angle = angle.x - ((60 / game->win_size.x) *
				(game->win_size.x - nb_col));
		if (d_angle < 0)
			d_angle = 360 - d_angle;
		stop = search_stop_pos(d_angle, map, player);
		stop = trace_segment(player->pos, stop, map);
	}
}

t_mlx_img		*raycast(t_mlx *game, char **map, t_player *player)
{
//	double		cam_proj_dist;
	t_mlx_img	*img;

//	cam_proj_dist = (double)game->win_size.x / tan(30);
	img = new_image(game->mlx, game->win_size.x, game->win_size.y);
}
