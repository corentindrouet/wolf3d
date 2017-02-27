/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdrouet <cdrouet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 11:28:47 by cdrouet           #+#    #+#             */
/*   Updated: 2017/02/27 15:17:02 by cdrouet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

t_mlx_img	*raycast(t_mlx *game, char **map, t_player *player)
{
	t_pts	angle;
	double	cam_proj_dist;

	angle.x = player.angle + 30 - (player.angle >= 330) ? 360 : 0;
	angle.x = player.angle - 30 + (player.angle < 30) ? 360 : 0;
	cam_proj_dist = (double)game->win_size.x / tan(30);
}
