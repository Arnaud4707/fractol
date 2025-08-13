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

void	calcule_a(t_vars *vars, int x, int y)
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
		vars->zr = (vars->zr - vars->zi) / 2;
		vars->zi = (tmp + vars->zi) / 2;
		i++;
	}
	if (i >= (int)vars->max_iteration)
		my_mlx_pixel_put(vars->img, x, y, 0x000000);
	else
	{
		my_mlx_pixel_put(vars->img, x, y, vars->palette[i]);
	}
}

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

void	draw_segment(t_vars *vars, double x1, double y1, double x2, double y2, int color)
{
    my_mlx_pixel_put(vars->img, (int)x1, (int)y1, color);
    int steps = fmax(fabs(x2 - x1), fabs(y2 - y1));
    double dx = (x2 - x1) / steps;
    double dy = (y2 - y1) / steps;
    for (int i = 0; i < steps; i++) {
        x1 += dx;
        y1 += dy;
        my_mlx_pixel_put(vars->img, (int)x1, (int)y1, color);
    }
}

void	dragon(t_vars *vars, double x1, double y1, double x2, double y2, int iter)
{
    if (iter == 0) {
        draw_segment(vars, x1, y1, x2, y2, 0x00FFFFFF);
        return;
    }

    double mx = (x1 + x2) / 2;
    double my = (y1 + y2) / 2;

    double dx = (x2 - x1) / 2;
    double dy = (y2 - y1) / 2;
    double rx = mx - dy;
    double ry = my + dx;

    dragon(vars, x1, y1, rx, ry, iter - 1);
    dragon(vars, x2, y2, rx, ry, iter - 1);
}

void	calcule_dragon(t_vars *vars)
{
	double ax = vars->xmin + (vars->xmax - vars->xmin) * 0.25;
	double ay = (vars->ymin + vars->ymax) / 2;
	double bx = vars->xmin + (vars->xmax - vars->xmin) * 0.75;
	double by = ay;

	(void)ax;
	(void)ay;
	(void)bx;
	(void)by;
	
	dragon(vars, 200, 400, 600, 400, 15);
}