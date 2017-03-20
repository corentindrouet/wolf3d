/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdrouet <cdrouet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/16 13:43:56 by cdrouet           #+#    #+#             */
/*   Updated: 2017/03/20 11:22:28 by cdrouet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void	side_move(int keycode, t_all *param)
{
	param->player->angle += ((keycode == LEFT || keycode == D_A) ? 2 : -2);
	if (param->player->angle >= 360)
		param->player->angle = 0;
	else if (param->player->angle < 0)
		param->player->angle = 360 + param->player->angle;
}

static void	up_down_move(int keycode, t_all *param)
{
	double	new_x;
	double	new_y;

	new_x = (((keycode == UP || keycode == D_W) ?
				1 : -1) * (8 * cos(RAD(param->player->angle))));
	new_y = (((keycode == UP || keycode == D_W) ?
				-1 : 1) * (8 * sin(RAD(param->player->angle))));
	if (!verif_wall(param->player->pos.x + new_x,
				param->player->pos.y + new_y, param->map))
	{
		param->player->extend.x += ((new_x >= 1 || new_x <= -1) ?
				fmod(new_x, (int)new_x) : new_x);
		param->player->extend.y += ((new_y >= 1 || new_y <= -1) ?
				fmod(new_y, (int)new_y) : new_y);
		param->player->pos.x += ((int)new_x + (int)param->player->extend.x);
		param->player->pos.y += ((int)new_y + (int)param->player->extend.y);
		if (param->player->extend.x >= 1 || param->player->extend.x <= -1)
			param->player->extend.x = fmod(param->player->extend.x,
					(int)param->player->extend.x);
		if (param->player->extend.y >= 1 || param->player->extend.y <= -1)
			param->player->extend.y = fmod(param->player->extend.y,
					(int)param->player->extend.y);
	}
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
