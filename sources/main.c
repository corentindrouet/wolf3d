/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdrouet <cdrouet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/23 11:22:20 by cdrouet           #+#    #+#             */
/*   Updated: 2017/03/16 14:24:47 by cdrouet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include <stdio.h>

static int	keypress(int keycode, t_all *param)
{
	int	i;

	if (keycode == ESC)
	{
		mlx_destroy_window(param->mlx->mlx, param->mlx->win);
		mlx_destroy_image(param->mlx->mlx, param->img->img);
		free(param->mlx->mlx);
		free(param->mlx);
		free(param->player);
		i = 0;
		while (param->map[i])
			free(param->map[i++]);
		free(param->map);
		exit(0);
	}
	ft_bzero(param->img->str_img,
			param->mlx->win_size.y * param->img->size_line);
	move(keycode, param);
	print_wall_to_img(param);
	mlx_clear_window(param->mlx->mlx, param->mlx->win);
	mlx_put_image_to_window(param->mlx->mlx, param->mlx->win,
			param->img->img, 0, 0);
	return (0);
}

static void	init_mlx_window(t_mlx *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		exit(0);
	game->win_size.x = 640;
	game->win_size.y = 400;
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
}

static char	**read_map(void)
{
	int		fd;
	char	buff[257];
	int		ret;
	char	*str;
	char	**splited;

	buff[256] = '\0';
	fd = open("map1.map", O_RDONLY);
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
	return (splited);
}

int			main(void)
{
	t_all		all_structs;

	all_structs.map = read_map();
	all_structs.mlx = malloc(sizeof(t_mlx));
	init_mlx_window(all_structs.mlx);
	start_game(&all_structs);
	mlx_hook(all_structs.mlx->win, 2, 0, keypress, &all_structs);
	mlx_loop(all_structs.mlx->mlx);
	return (0);
}
