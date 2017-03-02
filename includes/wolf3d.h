/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdrouet <cdrouet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/23 13:18:36 by cdrouet           #+#    #+#             */
/*   Updated: 2017/03/02 09:14:51 by cdrouet          ###   ########.fr       */
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
t_mlx_img		*raycast(t_all *all_structs);
int				tab_len(char **tab);
t_pts			trace_segment(t_pts start, t_pts stop, char **map);
t_pts			third_ca(t_pts d, t_pts start, t_pts stop, char **map);
t_pts			second_ca(t_pts d, t_pts start, t_pts stop, char **map);
t_pts			last_ca(t_pts d, t_pts start, t_pts stop, char **map);
t_pts			first_ca(t_pts d, t_pts start, t_pts stop, char **map);
t_pts			d_x_pos(t_pts d, t_pts start, t_pts stop, char **map);
t_pts			d_x_neg(t_pts d, t_pts start, t_pts stop, char **map);
int				verif_wall(int x, int y, char **map);
void			print_wall_to_img(t_mlx_img *img, t_all *all);
t_pts			search_pts_in_space(t_all *all, double angle, double uncorrect);

#endif
