/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdrouet <cdrouet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/23 11:22:20 by cdrouet           #+#    #+#             */
/*   Updated: 2017/02/28 15:04:27 by cdrouet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static int	keypress(int keycode, t_mlx *param)
{
	if (keycode == 53)
	{
		mlx_destroy_window(param->mlx, param->win);
		free(param->mlx);
		exit(0);
	}
	return (0);
}

static void	init_mlx_window(t_mlx *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		exit(0);
	game->win = mlx_new_window(game->mlx, 320, 200, "wolf3d");
	if (!game->win)
	{
		free(game->mlx);
		exit(0);
	}
	game->win_size.x = 320;
	game->win_size.y = 200;
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
	char	buff[256];
	int		ret;
	char	*str;
	char	**splited;

	fd = open("map.map", O_RDONLY);
	if (fd < 0)
		exit(0);
	ret = 256;
	str = NULL;
	while (ret == 256)
		if ((ret = read(fd, buff, 256)) >= 0)
			concat(buff, &str);
	splited = ft_strsplit(str, '\n');
	free(str);
	return (splited);
}

int			main(void)
{
	t_mlx		game;
	char		**map;

	map = read_map();
	init_mlx_window(&game);
	start_game(&game, map);
	mlx_hook(game.win, 2, 0, keypress, &game);
	mlx_loop(game.mlx);
	return (0);
}
