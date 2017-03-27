/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   precalculing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdrouet <cdrouet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/20 14:35:36 by cdrouet           #+#    #+#             */
/*   Updated: 2017/03/27 11:21:09 by cdrouet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static double	*init_math(double (*f)(double), t_all *all)
{
	double	*dbl;
	int		i;
	int		mapping_size;

	all->index_divide = ((double)ANGLE / (double)all->mlx->win_size.x);
	mapping_size = (360 / all->index_divide);
	dbl = (double*)malloc(sizeof(double) * mapping_size);
	i = 0;
	while (i < mapping_size)
	{
		dbl[i] = f(RAD(i * all->index_divide));
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
