/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdrouet <cdrouet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/23 11:22:20 by cdrouet           #+#    #+#             */
/*   Updated: 2017/03/30 10:25:39 by cdrouet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static int	keypress(int keycode, t_all *param)
{
	if (keycode == ESC)
		exit_properly(param);
	if (keycode == ESP)
		param->options.enable_texture = (param->options.enable_texture) ? 0 : 1;
	move(keycode, param);
	return (0);
}

static void	init_mlx_window(t_mlx *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		exit(0);
	game->win_size.x = 960;
	game->win_size.y = 600;
	game->win = mlx_new_window(game->mlx, game->win_size.x,
			game->win_size.y, "wolf3d");
	if (!game->win)
	{
		free(game->mlx);
		exit(0);
	}
}

int			main(void)
{
	t_all		all_structs;

	all_structs.texture[0] = read_bmp("img/Wall.bmp");
	all_structs.texture[1] = read_bmp("img/Wall2.bmp");
	all_structs.texture[2] = read_bmp("img/Wall3.bmp");
	all_structs.texture[3] = read_bmp("img/Wall4.bmp");
	all_structs.options.texture_problem = 0;
	if (!all_structs.texture[0] || !all_structs.texture[1]
			|| !all_structs.texture[2] || !all_structs.texture[3])
		all_structs.options.texture_problem = 1;
	all_structs.map.map = read_map(&all_structs);
	if (!(all_structs.mlx = malloc(sizeof(t_mlx))))
		exit(0);
	init_mlx_window(all_structs.mlx);
	init_precompute(&all_structs);
	if (!all_structs.precomputed)
		exit(0);
	start_game(&all_structs);
	mlx_hook(all_structs.mlx->win, 2, 0, keypress, &all_structs);
	mlx_hook(all_structs.mlx->win, 17, (1L << 17), close_event, &all_structs);
	mlx_loop_hook(all_structs.mlx->mlx, auto_refresh_function, &all_structs);
	mlx_loop(all_structs.mlx->mlx);
	return (0);
}
