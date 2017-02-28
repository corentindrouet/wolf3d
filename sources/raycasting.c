/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdrouet <cdrouet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 11:28:47 by cdrouet           #+#    #+#             */
/*   Updated: 2017/02/28 09:28:22 by cdrouet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static t_pts	search_stop_pos(double angle, char **map, t_player *player)
{
	t_pts	ret;
	int		*calcul;
	int		*pos;

//	ret = (t_pts*)malloc(sizeof(t_pts));
	if ((angle < 45 && angle >= 315) || (angle > 135 && angle <= 225))
		




		ret.y = player->pos.y + ((((ft_strlen(map[0]) * 64) - player->pos.y)
				/ sin(((180 - (90 + angle)) * M_PI) / 180))
				* sin((angle * M_PI) / 180));
}

static void		print_wall_to_img(t_mlx_img *img, char **map, t_player *player,
		t_mlx *game)
{
	t_pts		angle;
	double		res;
	int			nb_col;

	angle.x = player.angle + 30 - (player.angle >= 330) ? 360 : 0;
	angle.y = player.angle - 30 + (player.angle < 30) ? 360 : 0;
	nb_col = game->win_size.x;
	while (nb_col > 0)
	{

	}
}

t_mlx_img		*raycast(t_mlx *game, char **map, t_player *player)
{
//	double		cam_proj_dist;
	t_mlx_img	*img;

//	cam_proj_dist = (double)game->win_size.x / tan(30);
	img = new_image(game->mlx, 320, 200);
}
