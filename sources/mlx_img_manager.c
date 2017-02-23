/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_img_manager.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdrouet <cdrouet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/23 13:20:41 by cdrouet           #+#    #+#             */
/*   Updated: 2017/02/23 14:31:08 by cdrouet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

t_mlx_img	*new_image(void *mlx, int x, int y)
{
	t_mlx_img	*img;

	img = (t_mlx_img*)malloc(sizeof(t_mlx_img));
	img->img_size.x = x;
	img->img_size.y = y;
	img->img = mlx_new_image(mlx, x, y);
	img->str_img = mlx_get_data_addr(img->img, &(img->bits_per_pixel),
			&(img->size_line), &(img->endian));
	return (img);
}

int			write_img(int x, int y, t_mlx_img *img, int color)
{
	if (x < img->img_size.x && x >= 0 && y < img->img_size.y && y >= 0)
	{
		img->str_img[(y * img->size_line) + (x * img->bits_per_pixel / 8)] =
			(color & 0x00FF0000) >> 16;
		img->str_img[(y * img->size_line) + (x * img->bits_per_pixel / 8) + 1] =
			(color & 0x0000FF00) >> 8;
		img->str_img[(y * img->size_line) + (x * img->bits_per_pixel / 8) + 2] =
			color & 0x000000FF;
		return (1);
	}
	return (0);
}
