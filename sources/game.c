/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdrouet <cdrouet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 12:48:39 by cdrouet           #+#    #+#             */
/*   Updated: 2017/02/28 08:24:57 by cdrouet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d"

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
	player->angle = 0;
}

void		start_game(t_mlx *game, char **map)
{
	t_mlx_img	*img;
	t_player	player;

	init_player(map, &player);
	img = raycast(game, map, &player);
	mlx_put_image_to_window(game->mlx, game->win, img, 0, 0);
}
