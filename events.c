/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amugisha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 16:26:27 by amugisha          #+#    #+#             */
/*   Updated: 2025/01/07 19:58:27 by amugisha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "mlx/mlx.h"
#include "header.h"
#include <stdio.h>
#include <unistd.h>
#include <math.h>

int	closey(t_vars *vars)
{
	if (vars->img && vars->img->img)
		mlx_destroy_image(vars->mlx, vars->img->img);
	if (vars->win)
		mlx_destroy_window(vars->mlx, vars->win);
	mlx_destroy_display(vars->mlx);
	free(vars->mlx);
	free(vars->img);
	free(vars->palette);
	exit(0);
	return (0);
}

int	zoom(int button, int x, int y, t_vars *vars)
{
	double	tmpx;
	double	tmpy;

	tmpx = (vars->xmax - vars->xmin) * ((double)(x) / vars->largeur);
	tmpy = (vars->ymax - vars->ymin) * ((double)(y) / vars->hauteur);
	mlx_clear_window(vars->mlx, vars->win);
	action_zoom(button, tmpx, tmpy, vars);
	set_color(vars->color, vars);
	if (vars->f == 1)
		fractal(vars, calcule_m);
	else
		fractal(vars, calcule_j);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img->img, 0, 0);
	return (0);
}

int	arrow(int keycode, t_vars *vars)
{
	mlx_clear_window(vars->mlx, vars->win);
	if (keycode == 65361)
		horizontal(keycode, vars);
	else if (keycode == 65363)
		horizontal(keycode, vars);
	else if (keycode == 65362)
		vertical(keycode, vars);
	else if (keycode == 65364)
		vertical(keycode, vars);
	if (vars->f == 1)
		fractal(vars, calcule_m);
	else
		fractal(vars, calcule_j);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img->img, 0, 0);
	return (0);
}

int	julia_move(int x, int y, t_vars *vars)
{
	if (vars->play == 1 && vars->f == 3)
	{
		vars->cr = x / vars->ix + vars->xmin;
		vars->ci = y / vars->iy + vars->ymin;
		mlx_clear_window(vars->mlx, vars->win);
		fractal(vars, calcule_j);
		mlx_put_image_to_window(vars->mlx, vars->win, vars->img->img, 0, 0);
	}
	return (0);
}

int	key(int keycode, t_vars *vars)
{
	(void)vars;
	if (keycode == 65307)
		closey(vars);
	else if (keycode == 65361 || keycode == 65363
		|| keycode == 65362 || keycode == 65364)
		arrow(keycode, vars);
	else if (keycode == 115)
		vars->play = 0;
	else if (keycode == 112)
		vars->play = 1;
	else if (keycode == 114 || keycode == 121 || keycode == 103
		|| keycode == 98 || keycode == 65436
		|| keycode == 65433 || keycode == 65435
		|| keycode == 32 || keycode == 65430
		|| keycode == 65437)
		set_color(keycode, vars);
	return (0);
}
