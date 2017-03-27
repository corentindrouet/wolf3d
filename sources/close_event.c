/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_event.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdrouet <cdrouet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/21 10:48:09 by cdrouet           #+#    #+#             */
/*   Updated: 2017/03/27 14:28:39 by cdrouet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int	auto_refresh_function(t_all *param)
{
	ft_bzero(param->img->str_img,
			param->mlx->win_size.y * param->img->size_line);
	print_wall_to_img(param);
	mlx_clear_window(param->mlx->mlx, param->mlx->win);
	mlx_put_image_to_window(param->mlx->mlx, param->mlx->win,
			param->img->img, 0, 0);
	return (0);
}

int	close_event(void *param)
{
	exit_properly(param);
	return (0);
}
