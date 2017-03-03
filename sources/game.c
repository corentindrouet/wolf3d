/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdrouet <cdrouet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 12:48:39 by cdrouet           #+#    #+#             */
/*   Updated: 2017/03/03 11:37:30 by cdrouet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include <stdio.h>

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
	player->pos.x = ((tmp - map[i]) * 64) + 32;
	player->pos.y = (i * 64) + 32;
	*tmp = '0';
	player->angle = 90;
}

int				tab_len(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

void		start_game(t_all *all_structs)
{
	all_structs->player = malloc(sizeof(t_player));
	init_player(all_structs->map, all_structs->player);
	raycast(all_structs);
	mlx_put_image_to_window(all_structs->mlx->mlx, all_structs->mlx->win,
			all_structs->img->img, 0, 0);
}
