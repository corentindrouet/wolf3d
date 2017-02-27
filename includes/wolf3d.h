/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdrouet <cdrouet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/23 13:18:36 by cdrouet           #+#    #+#             */
/*   Updated: 2017/02/27 12:49:50 by cdrouet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include "mlx.h"
# include "libft.h"
# define BLOCK_SIZE 64

typedef struct	s_pts
{
	int			x;
	int			y;
}				t_pts;

typedef struct	s_mlx
{
	void		*mlx;
	void		*win;
	t_pts		win_size;
}				t_mlx;

typedef struct	s_mlx_img
{
	void		*img;
	int			bits_per_pixel;
	int			size_line;
	int			endian;
	char		*str_img;
	t_pts		img_size;
}				t_mlx_img;

typedef struct	s_player
{
	t_pts		pos;
	short		angle;
}				t_player;

t_mlx_img		*new_image(void *mlx, int x, int y);
int				write_img(int x, int y, t_mlx_img *img, int color);
void			start_game(t_mlx game, char **map);
t_mlx_img		*raycast(t_mlx *game, char **map, t_player *player);

#endif
