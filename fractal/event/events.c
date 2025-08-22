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

#include "mlx/mlx.h"
#include "../../include/header.h"

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

	// printf("x : %d | y : %d\n", x, y);
	if (vars->f == 5 && button == 4)
		zoom_dragon(vars, 0.8);
	else if (vars->f == 5 && button == 5)
		zoom_dragon(vars, 1.2);
	else
	{
		tmpx = (vars->xmax - vars->xmin) * ((double)(x) / vars->largeur);
		tmpy = (vars->ymax - vars->ymin) * ((double)(y) / vars->hauteur);
		action_zoom(button, tmpx, tmpy, vars);
	}
	mlx_clear_window(vars->mlx, vars->win);
	if (vars->f == 1 || vars->f == 2 || vars->f == 3 || vars->f == 4)
		set_color(vars->color, vars);
	if (vars->f == 1)
		fractal(vars, calcule_m);
	else if (vars->f == 2 || vars->f == 3)
		fractal(vars, calcule_j);
	else if (vars->f == 4)
		fractal(vars, calcule_b);
	else if (vars->f == 7)
		buddhabrot_thread(vars);
	else if (vars->f == 9)
		buddhabrot_colored_thread(vars);
	else if (vars->f == 5)
		calcule_dragon(vars);
	if (vars->f != 10 && vars->f != 8)
		mlx_put_image_to_window(vars->mlx, vars->win, vars->img->img, 0, 0);
	return (0);
}
void	zoom_dragon(t_vars* vars, double i)
{
	double cx = (vars->xmin + vars->xmax) / 2.0;
    double cy = (vars->ymin + vars->ymax) / 2.0;
    double half_width = (vars->xmax - vars->xmin) * i / 2.0;
    double half_height = (vars->ymax - vars->ymin) * i / 2.0;

	vars->xmin = cx - half_width;
	vars->xmax = cx + half_width;
	vars->ymin = cy - half_height;
	vars->ymax = cy + half_height;
	if (vars->ymin > 700.0 || vars->xmin < 70.0)
	{
		vars->xmin = 200;
		vars->xmax = 400;
		vars->ymin = 600;
		vars->ymax = 400;
	}
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
	else if (vars->f == 2 || vars->f == 3)
		fractal(vars, calcule_j);
	else if (vars->f == 4)
		fractal(vars, calcule_b);
	else if (vars->f == 7)
		buddhabrot_thread(vars);
	else if (vars->f == 9)
		buddhabrot_colored_thread(vars);
	else if (vars->f == 10)
		buddhabrot_colored_thread(vars);
	else if (vars->f == 5)
		calcule_dragon(vars);
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
	vars->key = keycode;
	if (vars->f == 1 || vars->f == 2 || vars->f == 3 || vars->f == 4 || vars->f == 5)
	{
		if (keycode == 65361 || keycode == 65363
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
	}
	else
	{
		if (vars->current_key != keycode && (keycode == 114 || keycode == 99 || keycode == 103
			|| keycode == 98 || keycode == 112 || keycode == 121 || keycode == 32
			|| keycode == 65436 || keycode == 65433 || keycode == 65435 || keycode == 65430) && vars->f == 7)
			set_color(keycode, vars);
		else if (vars->current_key != keycode && (keycode == 32 || keycode == 65436) && vars->f == 9)
			set_color(keycode, vars);
		else if ((keycode == 114 || keycode == 121 || keycode == 103
			|| keycode == 98 || keycode == 65436
			|| keycode == 65433 || keycode == 65435
			|| keycode == 32 || keycode == 65430
			|| keycode == 65437) && (vars->f == 10 || vars->f == 8))
			palette_color(keycode, vars);
	}
	printf("%d\n", keycode);
	return (0);
}
