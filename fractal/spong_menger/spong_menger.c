/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_b.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amugisha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 03:21:35 by amugisha          #+#    #+#             */
/*   Updated: 2025/01/06 04:44:05 by amugisha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/header.h"

int inMenger2D(double x, double y, int maxIter) {
    for (int i = 0; i < maxIter; i++) {
        int xi = ((int)floor(x)) % 3;
        int yi = ((int)floor(y)) % 3;

        if (xi == 1 && yi == 1) {
            return 0;
        }

        x /= 3.0;
        y /= 3.0;
    }
    return 1;
}

void	drawMenger2D(t_vars *vars, int depth)
{
    for (int y = 0; y < vars->hauteur; y++) {
        for (int x = 0; x < vars->largeur; x++) {
            double nx = (double)x / vars->largeur;
            double ny = (double)y / vars->hauteur;

            nx *= pow(3, depth);
            ny *= pow(3, depth);

            if (inMenger2D(nx, ny, depth)) {
                my_mlx_pixel_put(vars->img, x, y, 0xFFFFFF);
            } else {
                my_mlx_pixel_put(vars->img, x, y, 0x000000);
            }
        }
    }
}
