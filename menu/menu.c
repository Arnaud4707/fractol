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

int	loop_hook_display_menu(void* arg)
{
	t_vars *vars = (t_vars *)arg;
	background(vars);
	button_start(vars);
    mlx_put_image_to_window(vars->mlx, vars->win, vars->img->img, 0, 0);
	// mlx_string_put(vars->mlx, vars->win, 351, 401, 0x000000, "START");
	// mlx_string_put(vars->mlx, vars->win, 350, 400, vars->color, "START");
    usleep(50000);
	return (0);
}

void	background(t_vars* vars)
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
            double wave =
                8.0 * sin(0.05 * x + t) +
                5.0 * cos(0.04 * y + t * 0.8) +
                4.0 * sin(0.03 * (x + y) + t * 1.2);
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
				my_mlx_pixel_put(vars->img, x, y, vars->color);
		}
	}
	for (int y = 0; y < vars->hauteur; y++)
	{
		for (int x = 280; x <= 284; x++)
		{
			if (y > i && y < j)
				my_mlx_pixel_put(vars->img, x, y, vars->color);
		}
		for (int x = 516; x <= 520; x++)
		{
			if (y > i && y < j)
				my_mlx_pixel_put(vars->img, x, y, vars->color);
		}
	}
}

void	menu(t_vars* vars)
{
	mlx_loop_hook(vars->mlx, loop_hook_display_menu, vars);
}