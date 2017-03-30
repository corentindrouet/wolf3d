/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdrouet <cdrouet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/23 11:22:20 by cdrouet           #+#    #+#             */
/*   Updated: 2017/03/30 09:14:33 by cdrouet          ###   ########.fr       */
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

static void	concat(char *buff, char **str)
{
	char	*tmp;

	tmp = NULL;
	if (!(*str))
		*str = ft_strjoin(buff, "");
	else
	{
		tmp = ft_strjoin(*str, buff);
		free(*str);
		*str = tmp;
	}
	if (!(*str))
		exit(0);
}

static char	**read_map(t_all *all_structs)
{
	int		fd;
	char	buff[257];
	int		ret;
	char	*str;
	char	**splited;

	buff[256] = '\0';
	fd = open("map.map", O_RDONLY);
	if (fd < 0)
		exit(0);
	ret = 256;
	str = NULL;
	while (ret == 256)
	{
		ft_bzero(buff, 256);
		if ((ret = read(fd, buff, 256)) >= 0)
			concat(buff, &str);
	}
	splited = ft_strsplit(str, '\n');
	free(str);
	if (!check_valid_map(splited))
		exit(0);
	all_structs->map.size.x = (double)(ft_strlen(splited[0]) * BLOCK_SIZE);
	all_structs->map.size.y = (double)(tab_len(splited) * BLOCK_SIZE);
	return (splited);
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
