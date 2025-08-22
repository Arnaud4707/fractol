/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amugisha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 16:35:22 by amugisha          #+#    #+#             */
/*   Updated: 2025/01/06 21:27:25 by amugisha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx/mlx.h"
#include "../../include/header.h"

void	calcule_j(t_vars *vars, int x, int y)
{
	int		i;
	double	tmp;

	i = 0;
	vars->zr = x / vars->ix + vars->xmin;
	vars->zi = y / vars->iy + vars->ymin;
	while ((vars->zr * vars->zr + vars->zi * vars->zi) < 4
		&& i < vars->max_iteration)
	{
		tmp = vars->zr;
		vars->zr = (vars->zr * vars->zr) - (vars->zi * vars->zi) + vars->cr;
		vars->zi = (2 * vars->zi * tmp) + vars->ci;
		i++;
	}
	if (i >= (int)vars->max_iteration)
		my_mlx_pixel_put(vars->img, x, y, 0x00000000);
	else
		my_mlx_pixel_put(vars->img, x, y, vars->palette[i]);
}