/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdrouet <cdrouet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/23 11:22:20 by cdrouet           #+#    #+#             */
/*   Updated: 2017/02/23 14:30:28 by cdrouet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int		keypress(int keycode, t_mlx *param)
{
	if (keycode == 53)
	{
		mlx_destroy_window(param->mlx, param->win);
		exit(0);
	}
	return (0);
}

int main()
{
	t_mlx		game;
	t_mlx_img	*img;

	game.mlx = mlx_init();
	game.win = mlx_new_window(game.mlx, 200, 200, "prout");
	img = new_image(game.mlx, 200, 200);
	if (!write_img(150, 100, img, (int) 0x00FFFFFF))
		exit(0);
	mlx_put_image_to_window(game.mlx, game.win, img->img, 0, 0);
	mlx_hook(game.win, 2, 0, keypress, &game);
	mlx_loop(game.mlx);
	return (0);
}
