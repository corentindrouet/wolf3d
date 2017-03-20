/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdrouet <cdrouet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/16 13:43:56 by cdrouet           #+#    #+#             */
/*   Updated: 2017/03/20 14:29:07 by cdrouet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include <stdio.h>

static void	side_move(int keycode, t_all *param)
{
	param->player->angle += ((keycode == LEFT || keycode == D_A) ? 2 : -2);
	if (param->player->angle >= 360)
		param->player->angle = 0;
	else if (param->player->angle < 0)
		param->player->angle = 360 + param->player->angle;
	printf("angle %f\n", param->player->angle);
}

static void	up_down_move(int keycode, t_all *param)
{
	double	new_x;
	double	new_y;

	new_x = (((keycode == UP || keycode == D_W) ?
				1 : -1) * (8 * cos(RAD(param->player->angle))));
	new_y = (((keycode == UP || keycode == D_W) ?
				-1 : 1) * (8 * sin(RAD(param->player->angle))));
	if (!verif_wall(param->player->pos.x + new_x - 1,
				param->player->pos.y + new_y - 1, param->map))
	{
		param->player->pos.x += new_x;
		param->player->pos.y += new_y;
	}
	printf("player.x %f player.y %f\n", param->player->pos.x, param->player->pos.y);
}

void		move(int keycode, t_all *param)
{
	if (keycode == LEFT || keycode == RIGHT
			|| keycode == D_A || keycode == D_D)
		side_move(keycode, param);
	else if (keycode == UP || keycode == DOWN
			|| keycode == D_W || keycode == D_S)
		up_down_move(keycode, param);
}
