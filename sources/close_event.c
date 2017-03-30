/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_event.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdrouet <cdrouet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/21 10:48:09 by cdrouet           #+#    #+#             */
/*   Updated: 2017/03/30 08:46:06 by cdrouet          ###   ########.fr       */
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

int	close_event(t_all *param)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		free(param->texture[i]->str_img);
		free(param->texture[i]->tab_bmp);
		free(param->texture[i]);
		param->texture[i] = NULL;
		i++;
	}
	exit_properly(param);
	return (0);
}
