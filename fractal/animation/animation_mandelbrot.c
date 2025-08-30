/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation_mandelbrot.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amugisha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 16:35:22 by amugisha          #+#    #+#             */
/*   Updated: 2025/01/06 21:27:25 by amugisha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx/mlx.h"
#include "../../include/header.h"

void calcule_m_power(t_vars *vars, int x, int y, double power)
{
    int     i;

    i = 0;
    vars->cr = x / vars->ix + vars->xmin;
    vars->ci = y / vars->iy + vars->ymin;
    vars->zr = 0;
    vars->zi = 0;

    while ((vars->zr * vars->zr + vars->zi * vars->zi) < 4.0 && i < vars->max_iteration)
    {
        double r = sqrt(vars->zr * vars->zr + vars->zi * vars->zi);
        double theta = atan2(vars->zi, vars->zr);
        double r_power = pow(r, power);
        double theta_power = theta * power;
        vars->zr = r_power * cos(theta_power) + vars->cr;
        vars->zi = r_power * sin(theta_power) + vars->ci;
        i++;
    }

    if (i >= vars->max_iteration)
        my_mlx_pixel_put(vars->img, x, y, 0x000000);
    else
        my_mlx_pixel_put(vars->img, x, y, vars->palette[i]);
}

void fractal_power(t_vars *vars, double power)
{
    int x, y;

    vars->ix = WIDTH_ANIMATION / (vars->xmax - vars->xmin);
    vars->iy = HEIGHT_ANIMATION / (vars->ymax - vars->ymin);

    for (y = 0; y < HEIGHT_ANIMATION; y++)
    {
        for (x = 0; x < WIDTH_ANIMATION; x++)
        {
            calcule_m_power(vars, x, y, power);
        }
    }
}

int loop_hook_mandelbrot_pussance_n(t_vars *vars)
{
    static double power;
    static int direction = 1;
    static int initialisation = 1;
    static double power_max;

    if (initialisation)
    {
        power = (double) (vars->power_min);
        power_max = (double) (vars->power_max);
        initialisation = 0;
    }
    power += 0.05 * direction;

    if (power >= power_max)
        direction = -1;
    else if (power <= 2.0)
        direction = 1;

    fractal_power(vars, power);
	back(vars);
    mlx_put_image_to_window(vars->mlx, vars->win, vars->img->img, 0, 0);
    return (0);
}
