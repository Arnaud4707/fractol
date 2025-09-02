/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amugisha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 16:35:22 by amugisha          #+#    #+#             */
/*   Updated: 2025/01/06 21:27:25 by amugisha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx/mlx.h"
#include "../../include/header.h"

void zoom_towards_point(t_vars *vars, double target_x, double target_y, double factor)
{
    double dx = (vars->xmax - vars->xmin) / factor;
    double dy = (vars->ymax - vars->ymin) / factor;

    vars->xmin = target_x - dx / 2.0;
    vars->xmax = target_x + dx / 2.0;
    vars->ymin = target_y - dy / 2.0;
    vars->ymax = target_y + dy / 2.0;
}

int	loop_hook_zoom_mandelbrot(t_vars* vars)
{
    double tx = -1.62912294416127;
    double ty = -0.02065545758185;
	if (vars->step == 20)
	{
		if (vars->max_iteration < 100000.0)
			vars->max_iteration *= 1.2;
		vars->step = 0;
	}
	if (vars->ymax > -0.02064457)
		zoom_towards_point(vars, tx, ty, 1.02);
    fractal(vars, calcule_m);
	back(vars);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img->img, 0, 0);
    draw_next_back_audio(vars);
	usleep(33000);
	vars->step++;
	return (0);
}


