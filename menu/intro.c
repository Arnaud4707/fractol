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
    for (int y = 0; y < vars->hauteur; y++)
    {
        for (int x = 0; x < vars->largeur; x++)
        {
            // if (y >= 35 && y <= 125 && x >= 63 && x <= 188)
            if (y >= 25 && y <= 135 && x >= 50 && x <= 195)
                my_mlx_pixel_put(vars->img, x, y, 0x703005);
        }
    }
    overlay_image_cadre(vars, vars->img, vars->img_cadre, 50, 20);
	overlay_image_start(vars, vars->img, vars->img_police, 280, 355);
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

void	overlay_image_start(t_vars *vars, t_data *dst, t_data *src, int pos_x, int pos_y)
{
    int x, y;
    int src_color;
	int	test = 5000;
    for (y = 0; y < vars->img_police_h; y++)
    {
        for (x = 0; x < vars->img_police_w; x++)
        {
            char *src_pixel = src->addr + (y * src->line_length + x * (src->bits_per_pixel / 8));
            src_color = *(int *)src_pixel;

            if (src_color != 0xFFFFFF)
            {
                int dst_x = pos_x + x;
                int dst_y = pos_y + y;

                if (dst_x >= 0 && dst_x < vars->largeur &&
                    dst_y >= 0 && dst_y < vars->hauteur)
                {
                    char *dst_pixel = dst->addr + (dst_y * dst->line_length + dst_x * (dst->bits_per_pixel / 8));
                    *(int *)dst_pixel = vars->color_start + test;
					test += 10;
                }
            }
        }
    }
}

void	overlay_image_on(t_vars *vars, t_data *dst, t_data *src, int pos_x, int pos_y)
{
    int x, y;
    int src_color;

    for (y = 0; y < vars->img_on_h; y++)
    {
        for (x = 0; x < vars->img_on_w; x++)
        {
            char *src_pixel = src->addr + (y * src->line_length + x * (src->bits_per_pixel / 8));
            src_color = *(int *)src_pixel;

            if (src_color != 0x000000)
            {
                int dst_x = pos_x + x;
                int dst_y = pos_y + y;

                if (dst_x >= 0 && dst_x < vars->largeur &&
                    dst_y >= 0 && dst_y < vars->hauteur)
                {
                    char *dst_pixel = dst->addr + (dst_y * dst->line_length + dst_x * (dst->bits_per_pixel / 8));
                    *(int *)dst_pixel = src_color;
                }
            }
        }
    }
}

void	overlay_image_cadre(t_vars *vars, t_data *dst, t_data *src, int pos_x, int pos_y)
{
    int x, y;
    int src_color;

    for (y = 0; y < vars->img_cadre_h; y++)
    {
        for (x = 0; x < vars->img_cadre_w; x++)
        {
            char *src_pixel = src->addr + (y * src->line_length + x * (src->bits_per_pixel / 8));
            src_color = *(int *)src_pixel;
            if (src_color != 0xFF0000)
            {
                int dst_x = pos_x + x;
                int dst_y = pos_y + y;

                if (dst_x >= 0 && dst_x < vars->largeur &&
                    dst_y >= 0 && dst_y < vars->hauteur)
                {
                    char *dst_pixel = dst->addr + (dst_y * dst->line_length + dst_x * (dst->bits_per_pixel / 8));
                    *(int *)dst_pixel = src_color;
                }
            }
        }
    }
}
