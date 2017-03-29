/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdrouet <cdrouet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 12:48:39 by cdrouet           #+#    #+#             */
/*   Updated: 2017/03/29 14:11:13 by cdrouet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void	init_player(char **map, t_player *player)
{
	int		i;
	char	*tmp;

	i = 0;
	while (map[i])
	{
		if ((tmp = ft_strchr(map[i], 'x')))
			break ;
		i++;
	}
	player->pos.x = ((tmp - map[i]) * BLOCK_SIZE) + (BLOCK_SIZE / 2);
	player->pos.y = (i * BLOCK_SIZE) + (BLOCK_SIZE / 2);
	player->extend.x = 0;
	player->extend.y = 0;
	*tmp = '0';
	player->angle = 0;
}

int			verif_wall(int x, int y, t_map *map)
{
	if (y >= (int)map->size.y || y < 0 ||
			x >= (int)map->size.x || x < 0)
		return (0);
	return (map->map[y / BLOCK_SIZE][x / BLOCK_SIZE] - '0');
}

int			tab_len(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

double		angle_beta(double angle, t_player *player)
{
	if (player->angle < 29 && angle >= 329)
		return (angle - (player->angle + 360));
	if (player->angle > 329 && angle < 29)
		angle += 360;
	return (angle - (double)player->angle);
}

void		start_game(t_all *all_structs)
{
	all_structs->player = malloc(sizeof(t_player));
	init_player(all_structs->map.map, all_structs->player);
	all_structs->options.enable_texture = 1;
	all_structs->img = new_image(all_structs->mlx->mlx,
			all_structs->mlx->win_size.x,
			all_structs->mlx->win_size.y);
}
