/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdrouet <cdrouet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 09:07:55 by cdrouet           #+#    #+#             */
/*   Updated: 2017/03/30 10:25:31 by cdrouet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static int	only_character(char *str, char *c)
{
	int	i;
	int	j;
	int	cont;
	int	len;
	int c_len;

	i = 0;
	len = ft_strlen(str);
	c_len = ft_strlen(c);
	while (i < len)
	{
		j = 0;
		cont = 0;
		while (j < c_len)
		{
			if (str[i] == c[j])
				cont++;
			j++;
		}
		if (!cont)
			return (0);
		i++;
	}
	return (1);
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

static char	*str_map(int fd)
{
	char	buff[257];
	int		ret;
	int		total_ret;
	char	*str;

	buff[256] = '\0';
	ret = 256;
	total_ret = 0;
	str = NULL;
	while (ret == 256)
	{
		ft_bzero(buff, 256);
		if ((ret = read(fd, buff, 256)) >= 0)
			concat(buff, &str);
		total_ret += ret;
	}
	if (!total_ret)
		exit(0);
	return (str);
}

char		**read_map(t_all *all_structs)
{
	int		fd;
	char	*str;
	char	**splited;

	fd = open("map.map", O_RDONLY);
	if (fd < 0)
		exit(0);
	str = str_map(fd);
	splited = ft_strsplit(str, '\n');
	free(str);
	if (!check_valid_map(splited))
		exit(0);
	all_structs->map.size.x = (double)(ft_strlen(splited[0]) * BLOCK_SIZE);
	all_structs->map.size.y = (double)(tab_len(splited) * BLOCK_SIZE);
	return (splited);
}

int			check_valid_map(char **map)
{
	int	x;
	int	y;
	int	p;

	x = 0;
	p = 0;
	y = ft_strlen(map[x]);
	if (!only_character(map[x], "1")
			|| !only_character(map[tab_len(map) - 1], "1"))
		return (0);
	x++;
	while (x < (tab_len(map) - 1))
	{
		if (map[x][0] == '0' || map[x][y - 1] == '0'
				|| (int)ft_strlen(map[x]) != y)
			return (0);
		if (ft_strchr(map[x], 'x') && map[x][0] != 'x'
				&& map[x][ft_strlen(map[x]) - 1] != 'x')
			p = 1;
		y = ft_strlen(map[x]);
		x++;
	}
	return ((p == 1 && tab_len(map) > 2 && ft_strlen(map[0]) > 2) ? 1 : 0);
}
