/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intro.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amugisha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 14:45:54 by amugisha          #+#    #+#             */
/*   Updated: 2025/01/07 22:33:26 by amugisha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx/mlx.h"
#include "include/header.h"

void	intro(t_vars* vars)
{
	background_intro(vars);
	loop_hook_cube(vars);
	// cube(vars);
	button_start(vars);
	letter_s(vars);
    mlx_put_image_to_window(vars->mlx, vars->win, vars->img->img, 0, 0);
    usleep(30000);
}

void	background_intro(t_vars* vars)
{
	static double t = 0;

	for (int y = 0; y < vars->hauteur; y++)
	{
		for (int x = 0; x < vars->largeur; x++)
		{
			int r = 51;
			int g = 153;
			int b = 255;
			int color = (r << 16) | (g << 8) | b;
			my_mlx_pixel_put(vars->img, x, y, color);

		}
	}

	for (int y = 0; y < vars->hauteur; y += 10)
	{
		for (int x = 0; x < vars->largeur; x += 10)
		{
			double cx = vars->largeur / 2.0;
			double cy = vars->hauteur / 2.0;
			double dx = x - cx;
			double dy = y - cy;
			double dist = sqrt(dx*dx + dy*dy);

			double wave = 10.0 * sin(0.05 * dist - t);

			int newY = (int)(y + wave);
			if (newY >= 0 && newY < vars->hauteur)
				my_mlx_pixel_put(vars->img, x, newY, 0xFFFFFF);
		}
	}
	t += 0.1;
	return ;
}

void	button_start(t_vars* vars)
{
	int i;
	int j;

	i = 370;
	j = 430;
	for (int y = 0; y < vars->hauteur; y++)
	{
		for (int x = 0; x < vars->largeur; x++)
		{
			if (((y >= i && y <= (i + 4)) || (y >= (j - 4) && y <= j)) && (x > 279 && x < 521))
				my_mlx_pixel_put(vars->img, x, y, vars->color_start);
		}
	}
	for (int y = 0; y < vars->hauteur; y++)
	{
		for (int x = 280; x <= 284; x++)
		{
			if (y > i && y < j)
				my_mlx_pixel_put(vars->img, x, y, vars->color_start);
		}
		for (int x = 516; x <= 520; x++)
		{
			if (y > i && y < j)
				my_mlx_pixel_put(vars->img, x, y, vars->color_start);
		}
	}
}

int loop_hook_cube(t_vars *vars)
{
    static double ax = 0, ay = 0, az = 0;

    draw_cube(vars, ax, ay, az);

    ax += 0.02;
    ay += 0.03;
    az += 0.01;

    return 0;
}