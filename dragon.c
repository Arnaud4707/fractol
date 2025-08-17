/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal_bis.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amugisha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 16:35:22 by amugisha          #+#    #+#             */
/*   Updated: 2025/01/06 21:27:25 by amugisha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx/mlx.h"
#include "header.h"

void	draw_segment(t_vars *vars, double x1, double y1, double x2, double y2, int color)
{
	static int ii = 0;

	ii++;
    my_mlx_pixel_put(vars->img, (int)x1, (int)y1, color * ii);
    int steps = fmax(fabs(x2 - x1), fabs(y2 - y1));
    double dx = (x2 - x1) / steps;
    double dy = (y2 - y1) / steps;
    for (int i = 0; i < steps; i++) {
        x1 += dx;
        y1 += dy;
        my_mlx_pixel_put(vars->img, (int)x1, (int)y1, color * ii);
    }
}

void	dragon(t_vars *vars, double x1, double y1, double x2, double y2, int iter)
{
    if (iter == 0) {
        draw_segment(vars, x1, y1, x2, y2, 0x00FF00FF);
        return;
    }

    double mx = (x1 + x2) / 2;
    double my = (y1 + y2) / 2;

    double dx = (x2 - x1) / 2;
    double dy = (y2 - y1) / 2;
    double rx = mx - dy;
    double ry = my + dx;

    dragon(vars, x1, y1, rx, ry, iter - 1);
    dragon(vars, x2, y2, rx, ry, iter - 1);
}

void	calcule_dragon(t_vars *vars)
{
	double ax = vars->xmin + (vars->xmax - vars->xmin) * 0.02;
	double ay = (vars->ymin + vars->ymax) / 2.5;
	double bx = vars->xmin + (vars->xmax - vars->xmin) * 1.5;
	double by = ay;

	memset(vars->img->addr, 0, vars->hauteur * vars->img->line_length);
	dragon(vars, ax, ay, bx, by, (int)vars->max_iteration);

}
