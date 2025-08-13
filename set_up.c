/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_up.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amugisha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 16:48:47 by amugisha          #+#    #+#             */
/*   Updated: 2025/01/19 21:49:02 by amugisha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx/mlx.h"
#include "header.h"
#include "stdlib.h"
#include <stdio.h>

void	palette_color(int keycode, t_vars *vars)
{
	if (keycode == 114)
		precalculate_colors_r(vars);
	else if (keycode == 121)
		precalculate_colors_y(vars);
	else if (keycode == 103)
		precalculate_colors_g(vars);
	else if (keycode == 98)
		precalculate_colors_b(vars);
	else if (keycode == 65436)
		precalculate_colors_1(vars);
	else if (keycode == 65433)
		precalculate_colors_2(vars);
	else if (keycode == 65435)
		precalculate_colors_3(vars);
	else if (keycode == 65430)
		precalculate_colors_4(vars);
	else if (keycode == 32)
		precalculate_colors(vars);
	else if (keycode == 65437)
		precalculate_colors_5(vars);
}

void	set_color(int keycode, t_vars *vars)
{
	palette_color(keycode, vars);
	vars->color = keycode;
	mlx_clear_window(vars->mlx, vars->win);
	if (vars->f == 1)
		fractal(vars, calcule_m);
	else if (vars->f == 2 || vars->f == 3)
		fractal(vars, calcule_j);
	else if (vars->f == 4)
		fractal(vars, calcule_b);
	else
		calcule_dragon(vars);

	mlx_put_image_to_window(vars->mlx, vars->win, vars->img->img, 0, 0);
}

int	vars_set_julia_move(t_vars *vars)
{
	vars->name = "Fractal Julia Move";
	vars->max_iteration = 50;
	vars->largeur = 500;
	vars->hauteur = 500;
	vars->xmin = -2;
	vars->xmax = 2;
	vars->ymin = -2;
	vars->ymax = 2;
	vars->f = 3;
	vars->color = 1;
	vars->play = 1;
	vars->zoom_i = 0;
	vars->palette = NULL;
	vars->cr = 0;
	vars->ci = 0;
	vars->zr = 0;
	vars->zi = 0;
	return (precalculate_colors(vars));
}

int	vars_set_burning_ship(t_vars *vars)
{
	vars->name = "Fractal Burning ship";
	vars->max_iteration = 50;
	vars->largeur = 800;
	vars->hauteur = 800;
	vars->xmin = -2;
	vars->xmax = 0.5;
	vars->ymin = -1.25;
	vars->ymax = 1.25;
	vars->f = 4;
	vars->color = 1;
	vars->play = 1;
	vars->zoom_i = 0;
	vars->palette = NULL;
	vars->cr = 0;
	vars->ci = 0;
	vars->zr = 0;
	vars->zi = 0;
	return (precalculate_colors(vars));
}

int	vars_set_dragon(t_vars *vars)
{
	vars->name = "Fractal Dragon Curse";
	vars->max_iteration = 50;
	vars->largeur = 800;
	vars->hauteur = 800;
	vars->xmin = -2;
	vars->xmax = 0.5;
	vars->ymin = -1.25;
	vars->ymax = 1.25;
	vars->f = 5;
	vars->color = 1;
	vars->play = 1;
	vars->zoom_i = 0;
	vars->palette = NULL;
	vars->cr = 0;
	vars->ci = 0;
	vars->zr = 0;
	vars->zi = 0;
	return (precalculate_colors(vars));
}


int	vars_set_mandelbrot(t_vars *vars)
{
	vars->name = "Fractal Mandelbrot";
	vars->max_iteration = 50;
	vars->largeur = 800;
	vars->hauteur = 800;
	vars->xmin = -2;
	vars->xmax = 0.5;
	vars->ymin = -1.25;
	vars->ymax = 1.25;
	vars->f = 1;
	vars->color = 1;
	vars->play = 1;
	vars->zoom_i = 0;
	vars->palette = NULL;
	vars->cr = 0;
	vars->ci = 0;
	vars->zr = 0;
	vars->zi = 0;
	return (precalculate_colors(vars));
}

int	vars_set_julia(t_vars *vars)
{
	vars->name = "Fractal Julia";
	vars->max_iteration = 50;
	vars->largeur = 700;
	vars->hauteur = 700;
	vars->xmin = -1.5;
	vars->xmax = 1.5;
	vars->ymin = -1.5;
	vars->ymax = 1.5;
	vars->f = 2;
	vars->color = 1;
	vars->play = 0;
	vars->zoom_i = 0;
	vars->palette = NULL;
	return (precalculate_colors(vars));
}
