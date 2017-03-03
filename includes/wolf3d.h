/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdrouet <cdrouet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/23 13:18:36 by cdrouet           #+#    #+#             */
/*   Updated: 2017/03/03 08:53:09 by cdrouet          ###   ########.fr       */
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
	double		angle;
}				t_player;

typedef struct	s_all
{
	t_mlx		*mlx;
	t_mlx_img	*img;
	t_player	*player;
	char		**map;
}				t_all;

t_mlx_img		*new_image(void *mlx, int x, int y);
int				write_img(int x, int y, t_mlx_img *img, int color);
void			start_game(t_all *all_structs);
void			raycast(t_all *all_structs);
int				tab_len(char **tab);
int				verif_wall(int x, int y, char **map);
void			print_wall_to_img(t_all *all);
double			search_pts_in_space(t_all *all, double angle);
double			angle_beta(double angle, t_player *player);

#endif
