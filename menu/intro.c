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

t_rgb hsl_to_rgb2(double h, double s, double l)
{
    double c = (1 - fabs(2*l - 1)) * s;
    double x = c * (1 - fabs(fmod(h / 60.0, 2) - 1));
    double m = l - c/2;
    double r=0,g=0,b=0;

    if (h < 60)
	{
		r = c;
		g = x;
		b = 0;
	}
    else if (h < 120){ r = x; g = c; b = 0; }
    else if (h < 180){ r = 0; g = c; b = x; }
    else if (h < 240){ r = 0; g = x; b = c; }
    else if (h < 300){ r = x; g = 0; b = c; }
    else             { r = c; g = 0; b = x; }

    t_rgb out;
    out.r = (int)((r + m) * 255);
    out.g = (int)((g + m) * 255);
    out.b = (int)((b + m) * 255);
    return out;
}

void	intro(t_vars* vars)
{
	background_intro(vars);
	draw_wave(vars);
	loop_hook_cube(vars);
	button_start(vars);
	letter_s(vars);
    mlx_put_image_to_window(vars->mlx, vars->win, vars->img->img, 0, 0);
	draw_next_back_audio(vars);
    usleep(20000);
}

void	background_intro(t_vars* vars)
{
	double hue   = fmod(vars->mid * 520.0, 340.0);
	double sat   = 0.4 + 0.35 * vars->treble;
	double light = 0.4 + 0.2 * vars->bass;

	static double sh = 0, ss = 0, sl = 0;
	double alpha = 0.1;
	sh = (1-alpha) * sh + alpha * hue;
	ss = (1-alpha) * ss + alpha * sat;
	sl = (1-alpha) * sl + alpha * light;

	t_rgb col = hsl_to_rgb2(sh, ss, sl);
	int bg_color = (col.r << 16) | (col.g << 8) | col.b;

	for (int y = 0; y < vars->hauteur; y++)
	{
		for (int x = 0; x < vars->largeur; x++)
		{
			my_mlx_pixel_put(vars->img, x, y, bg_color);
		}
	}
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
