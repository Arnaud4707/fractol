/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amugisha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 16:35:22 by amugisha          #+#    #+#             */
/*   Updated: 2025/01/06 21:27:25 by amugisha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx/mlx.h"
#include "header.h"

void	calcule_b(t_vars *vars, int x, int y)
{
	int		i;
	double	tmp;

	i = 0;
	vars->cr = x / vars->ix + vars->xmin;
	vars->ci = y / vars->iy + vars->ymin;
	vars->zr = 0;
	vars->zi = 0;
	while (((vars->zr * vars->zr) + (vars->zi * vars->zi)) < 4
		&& i < vars->max_iteration)
	{
		tmp = fabs(vars->zr);
		vars->zr = (vars->zr * vars->zr) - (vars->zi * vars->zi) + vars->cr;
		vars->zi = (2 * fabs(vars->zi) * tmp) + vars->ci;
		i++;
	}
	if (i >= (int)vars->max_iteration)
		my_mlx_pixel_put(vars->img, x, y, 0x000000);
	else
	{
		my_mlx_pixel_put(vars->img, x, y, vars->palette[i]);
	}
}

void	calcule_m(t_vars *vars, int x, int y)
{
	int		i;
	double	tmp;

	i = 0;
	vars->cr = x / vars->ix + vars->xmin;
	vars->ci = y / vars->iy + vars->ymin;
	vars->zr = 0;
	vars->zi = 0;
	while (((vars->zr * vars->zr) + (vars->zi * vars->zi)) < 4
		&& i < vars->max_iteration)
	{
		tmp = vars->zr;
		vars->zr = (vars->zr * vars->zr) - (vars->zi * vars->zi) + vars->cr;
		vars->zi = (2 * vars->zi * tmp) + vars->ci;
		i++;
	}
	if (i >= (int)vars->max_iteration)
		my_mlx_pixel_put(vars->img, x, y, 0x000000);
	else
	{
		my_mlx_pixel_put(vars->img, x, y, vars->palette[i]);
	}
}

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

void	fractal(t_vars *vars, void (*calcule)(t_vars *, int, int))
{
	int	x;
	int	y;

	vars->ix = vars->largeur / (vars->xmax - vars->xmin);
	vars->iy = vars->hauteur / (vars->ymax - vars->ymin);
	y = 0;
	while (y < vars->hauteur)
	{
		x = 0;
		while (x < vars->largeur)
		{
			calcule(vars, x, y);
			x++;
		}
		y++;
	}
}