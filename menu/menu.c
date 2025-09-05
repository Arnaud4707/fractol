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

void	menu(t_vars *vars)
{
	background_menu(vars);
	draw_wave(vars);
	loop_hook_cube(vars);
	back(vars);
    for (int y = 0; y < vars->hauteur; y++)
    {
        for (int x = 0; x < vars->largeur; x++)
        {
            if (y >= 35 && y <= 125 && x >= 63 && x <= 188)
                my_mlx_pixel_put(vars->img, x, y, 0x703005);
        }
    }
    overlay_image_cadre(vars, vars->img, vars->img_cadre, 50, 20);
    mlx_put_image_to_window(vars->mlx, vars->win, vars->img->img, 0, 0);
	draw_next_back_audio(vars);
	option(vars);
    usleep(20000);
}

void	background_menu(t_vars* vars)
{
	int r = (int)(255 * vars->mid);
	int g = (int)(153 * vars->treble);
	int b = 51;
	int bg_color = (r << 16) | (g << 8) | b;

	for (int y = 0; y < vars->hauteur; y++)
	{
		for (int x = 0; x < vars->largeur; x++)
		{
			my_mlx_pixel_put(vars->img, x, y, bg_color);
		}
	}
	return ;
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
