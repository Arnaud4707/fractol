/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amugisha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 14:45:54 by amugisha          #+#    #+#             */
/*   Updated: 2025/01/07 22:33:26 by amugisha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx/mlx.h"
#include "include/header.h"

void	drow_fractal(t_vars* vars)
{
	if (vars->f > 0 && vars->need_drow)
	{
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
		else if (vars->f == 12)
			drawMenger2D(vars, vars->max_iteration);
	}
}


void	app(t_vars* vars)
{
	if (vars->play_audio == 0)
	{
		vars->play_audio = 1;
		audio_play(vars);
	}
	analyse_audio(vars);
    if (vars->f == -1)
	{
        intro(vars);
	}
    else if (vars->f == -2)
	{
		menu(vars);
	}
	drow_fractal(vars);
	if (vars->f == 11)
		loop_hook_buddhabrot_thread(vars);
	else if (vars->f == 10)
		loop_hook_mandelbrot_pussance_n(vars);
	else if (vars->f == 8)
		loop_hook_zoom_mandelbrot(vars);
	else if (vars->f == 6)
		loop_hook_buddhabrot_thread_2(vars);
	if (vars->need_drow && vars->f != 8 && vars->f != 10 && vars->f != -1 && vars->f != -2)
	{
		back(vars);
		vars->need_drow = 0;
		mlx_put_image_to_window(vars->mlx, vars->win, vars->img->img, 0, 0);
		draw_next_back_audio(vars);
	}
}

void	on(t_vars* vars)
{
	for (int y = 0; y <= vars->hauteur; y++)
	{
		for (int x = 0; x <= vars->largeur; x++)
		{
			if ((y >= 265 && y <= 535) && (x >= 270 && x <= 535))
				my_mlx_pixel_put(vars->img, x, y, vars->color_on);
		}
	}
	overlay_image_on(vars, vars->img, vars->img_on, 240, 255);
    mlx_put_image_to_window(vars->mlx, vars->win, vars->img->img, 0, 0);
    usleep(60000);
}

int	loop_hook_master(void* arg)
{
	t_vars *vars = (t_vars *)arg;

	if (vars->f == -3)
		on(vars);
	else
		app(vars);
    return 0;
}
