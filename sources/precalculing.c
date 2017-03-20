/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   precalculing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdrouet <cdrouet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/20 14:35:36 by cdrouet           #+#    #+#             */
/*   Updated: 2017/03/20 15:22:49 by cdrouet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include <stdio.h>

static double	*init_math(double (*f)(double), t_all *all)
{
	double	*dbl;
	int		i;
	int		mapping_size;
	double	col_angle_size;

	col_angle_size = ((double)ANGLE / (double)all->mlx->win_size.x);
	mapping_size = (360 / col_angle_size);
	dbl = (double*)malloc(sizeof(double) * mapping_size);
	i = 0;
	while (i < mapping_size)
	{
		dbl[i] = f(RAD(i * col_angle_size));
		i++;
	}
	return (dbl);
}

void			init_precompute(t_all *all)
{
	all->precomputed = (t_precompute*)malloc(sizeof(t_precompute));
	if (all->precomputed)
	{
		all->precomputed->cos = init_math(cos, all);
		all->precomputed->sin = init_math(sin, all);
		all->precomputed->tan = init_math(tan, all);
	}
}
