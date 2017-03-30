/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdrouet <cdrouet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 09:07:55 by cdrouet           #+#    #+#             */
/*   Updated: 2017/03/30 09:15:47 by cdrouet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int		check_valid_map(char **map)
{
	int	x;
	int	y;

	x = 0;
	y = ft_strlen(map[x]);
	if (ft_strchr(map[x], '0') || ft_strchr(map[tab_len(map) - 1], '0'))
		return (0);
	while (x < tab_len(map))
	{
		if (map[x][0] == '0' || map[x][y - 1] == '0'
				|| (int)ft_strlen(map[x]) != y)
			return (0);
		y = ft_strlen(map[x]);
		x++;
	}
	return (1);
}
