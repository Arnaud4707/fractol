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

int	loop_hook_master(void* arg)
{
	t_vars *vars = (t_vars *)arg;

	if (vars->play_audio == 0)
	{
		vars->play_audio = 1;
		audio_play(vars);
	}
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
	}
    return 0;
}

void	menu(t_vars *vars)
{
	background_menu(vars);
	back(vars);
    mlx_put_image_to_window(vars->mlx, vars->win, vars->img->img, 0, 0);
	option(vars);
    usleep(30000);
}

void	background_menu(t_vars* vars)
{
	static double t = 0;

	for (int y = 0; y < vars->hauteur; y++)
	{
		for (int x = 0; x < vars->largeur; x++)
		{
			int r = 255;
			int g = 153;
			int b = 51;
			int color = (r << 16) | (g << 8) | b;
			my_mlx_pixel_put(vars->img, x, y, color);

		}
	}

	for (int y = 0; y < vars->hauteur; y += 10)
    {
        for (int x = 0; x < vars->largeur; x += 10)
        {
            double wave =
                8.0 * sin(0.00 * x + t) +
                5.0 * cos(0.04 * y + t * 0.8) +
                4.0 * sin(0.03 * (x + y) + t * 1.2);
            int newY = (int)(y + wave);
            if (newY >= 0 && newY < vars->hauteur)
                my_mlx_pixel_put(vars->img, x, newY, 0xFFFFFFFF);
        }
    }
	t += 0.1;
}

void	back(t_vars* vars)
{
	int i;
	i = 0;
	for (int y = 0; y < vars->hauteur; y++)
	{
		for (int x = 0; x < vars->largeur; x++)
		{
			if ((i >= 0) && (y >= vars->hauteur - 80 && y <= vars->largeur - 50)
				&& (x >= vars->largeur - 65 - i && x <= vars->largeur - 65))
                my_mlx_pixel_put(vars->img, x, y, vars->color_back);
			else if ((i <= 0) && (y >= vars->hauteur - 80 && y <= vars->largeur - 50)
				&& (x >= vars->largeur - 65 + i && x <= vars->largeur - 65))
				my_mlx_pixel_put(vars->img, x, y, vars->color_back);
			if ((y >= vars->hauteur - 69 && y <= vars->largeur - 61) && (x >= vars->largeur - 65 && x <= vars->largeur - 35))
				my_mlx_pixel_put(vars->img, x, y, vars->color_back);
		}
		if (((y >= (vars->hauteur - 80)) && (y <= (vars->largeur - 50))) && (i <= 15))
			i++;
		else if (((y >= (vars->hauteur - 80)) && (y <= (vars->largeur - 50))) && (i > 15))
			i -= 2 * i - 1;
	}
}
