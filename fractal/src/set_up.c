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
#include "../../include/header.h"

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
	if (vars->f != 7 && vars->f != 9 && vars->f != 11)
		palette_color(keycode, vars);
	vars->color = keycode;
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
	if (vars->f != 8 && vars->f != 10)
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
	vars->max_iteration = 15;
	vars->largeur = 800;
	vars->hauteur = 800;
	vars->xmin = 200;
	vars->xmax = 400;
	vars->ymin = 600;
	vars->ymax = 400;
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

int	vars_set_mandelbrot_zoom(t_vars *vars)
{
	vars->name = "Fractal Mandelbrot Z pussance 4";
	vars->max_iteration = 100;
	vars->largeur = 400;
	vars->hauteur = 400;
	vars->xmin = -2;
	vars->xmax = 0.5;
	vars->ymin = -1.25;
	vars->ymax = 1.25;
	vars->f = 8;
	vars->color = 1;
	vars->play = 1;
	vars->zoom_i = 0;
	vars->palette = NULL;
	vars->cr = 0;
	vars->ci = 0;
	vars->zr = 0;
	vars->zi = 0;
	return (precalculate_colors_5(vars));
}

int	vars_set_buddhabrot_animation_2(t_vars *vars)
{
	vars->name = "Fractal Buddhabrot animation 2";
	vars->max_iteration = 50;
	vars->largeur = WIDTH;
	vars->hauteur = HEIGHT;
	vars->xmin = -2;
	vars->xmax = 2;
	vars->ymin = -2;
	vars->ymax = 2;
	vars->f = 6;
	vars->color = 1;
	vars->play = 1;
	vars->zoom_i = 0;
	vars->palette = NULL;
	vars->cr = 0;
	vars->ci = 0;
	vars->zr = 0;
	vars->zi = 0;
	return (0);
}

int	vars_set_spondMenger(t_vars *vars, char* i)
{
	int nb;

	nb = ft_atoi(i);
	if (nb < 1 || nb > 639)
		return (-1);
	vars->name = "Fractal Spong of Mengert";
	vars->max_iteration = nb;
	vars->largeur = 800;
	vars->hauteur = 800;
	vars->xmin = -2;
	vars->xmax = 0.5;
	vars->ymin = -1.25;
	vars->ymax = 1.25;
	vars->f = 12;
	vars->color = 1;
	vars->play = 1;
	vars->zoom_i = 0;
	vars->palette = NULL;
	vars->cr = 0;
	vars->ci = 0;
	vars->zr = 0;
	vars->zi = 0;
	return (0);
}

int	vars_set_Buddhabrot(t_vars *vars)
{
	vars->name = "Fractal Buddhabrot";
	vars->max_iteration = 100;
	vars->largeur = WIDTH;
	vars->hauteur = HEIGHT;
	vars->xmin = -2;
	vars->xmax = 2;
	vars->ymin = -2;
	vars->ymax = 2;
	vars->f = 7;
	vars->color = 1;
	vars->play = 1;
	vars->key = 32;
	vars->current_key = 0;
	vars->zoom_i = 0;
	vars->palette = NULL;
	vars->cr = 0;
	vars->ci = 0;
	vars->zr = 0;
	vars->zi = 0;
	return (0);
}

int	vars_set_Menu(t_vars *vars)
{
	vars->name = "Fractal Menu";
	vars->max_iteration = 100;
	vars->largeur = 800;
	vars->hauteur = 800;
	vars->xmin = -2;
	vars->xmax = 2;
	vars->ymin = -2;
	vars->ymax = 2;
	vars->f = -1;
	vars->color = 0xFFFFFFFF;
	vars->play = 1;
	vars->key = 32;
	vars->current_key = 0;
	vars->zoom_i = 0;
	vars->palette = NULL;
	vars->cr = 0;
	vars->ci = 0;
	vars->zr = 0;
	vars->zi = 0;
	return (0);
}

int	vars_set_BuddhabrotA(t_vars *vars)
{
	vars->name = "Fractal Buddhabrot Animed";
	vars->max_iteration = 100;
	vars->largeur = WIDTH;
	vars->hauteur = HEIGHT;
	vars->xmin = -2;
	vars->xmax = 2;
	vars->ymin = -2;
	vars->ymax = 2;
	vars->f = 11;
	vars->color = 1;
	vars->play = 1;
	vars->zoom_i = 0;
	vars->palette = NULL;
	vars->cr = 0;
	vars->ci = 0;
	vars->zr = 0;
	vars->zi = 0;
	return (0);
}

int	vars_set_Buddhabrot2(t_vars *vars)
{
	vars->name = "Fractal Buddhabrot Colored";
	vars->max_iteration = 100;
	vars->largeur = WIDTH;
	vars->hauteur = HEIGHT;
	vars->xmin = -2;
	vars->xmax = 2;
	vars->ymin = -2;
	vars->ymax = 2;
	vars->f = 9;
	vars->color = 1;
	vars->key = 32;
	vars->play = 1;
	vars->zoom_i = 0;
	vars->palette = NULL;
	vars->cr = 0;
	vars->ci = 0;
	vars->zr = 0;
	vars->zi = 0;
	return (precalculate_color_buddhabrot(vars), 0);
}

int	vars_set_MandelbrotA(t_vars *vars, char *pmin, char* pmax)
{
	int p_min;
	int p_max;

	p_min = ft_atoi(pmin);
	p_max = ft_atoi(pmax);
	if (p_min < 2 || p_max > 10 || p_min > p_max)
		return (-1);
	vars->name = "Fractal Mandelbrot Animation";
	vars->max_iteration = 50;
	vars->largeur = WIDTH_ANIMATION;
	vars->hauteur = HEIGHT_ANIMATION;
	vars->xmin = -2;
	vars->xmax = 2;
	vars->ymin = -2;
	vars->ymax = 2;
	vars->f = 10;
	vars->power_min = p_min;
	vars->power_max = p_max;
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
	vars->max_iteration = 250;
	vars->largeur = 800;
	vars->hauteur = 800;
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
