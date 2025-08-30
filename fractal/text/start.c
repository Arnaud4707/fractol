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

void    letter_s(t_vars* vars)
{
    for (int y = 0; y < vars->hauteur; y++)
    {
        for (int x = 0; x < vars->largeur; x++)
        {
            if (((y >= 380 && y <= 384) || (y >= 396 && y <= 400)
                || (y >= 412 && y <= 416)) && (x >= 315 && x <= 335))
                my_mlx_pixel_put(vars->img, x, y, vars->color_start);
            if ((y >= 380 && y <= 400) && (x >= 315 && x <= 319))
                my_mlx_pixel_put(vars->img, x, y, vars->color_start);
            if ((y >= 400 && y <= 416) && (x >= 331 && x <= 335))
                my_mlx_pixel_put(vars->img, x, y, vars->color_start);
            // s
            if ((y >= 380 && y <= 384) && (x >= 350 && x <= 380))
                my_mlx_pixel_put(vars->img, x, y, vars->color_start);
            if ((y >= 380 && y <= 416) && (x >= 363 && x <= 367))
                my_mlx_pixel_put(vars->img, x, y, vars->color_start);
            // t
            if (((y >= 380 && y <= 384) || (y >= 396 && y <= 400))
                && (x >= 390 && x <= 410))
                my_mlx_pixel_put(vars->img, x, y, vars->color_start);
            if ((y >= 380 && y <= 416) && ((x >= 390 && x <= 394)
                || (x >= 406 && x <= 410)))
                my_mlx_pixel_put(vars->img, x, y, vars->color_start);
            // a
            if (((y >= 380 && y <= 384) || (y >= 396 && y <= 400)) && (x >= 420 && x <= 440))
                my_mlx_pixel_put(vars->img, x, y, vars->color_start);

            if ((y >= 380 && y <= 416) && (x >= 420 && x <= 424))
                my_mlx_pixel_put(vars->img, x, y, vars->color_start);

            if ((y >= 380 && y <= 400) && (x >= 436 && x <= 440))
                my_mlx_pixel_put(vars->img, x, y, vars->color_start);

            if ((y >= 400 && y <= 416) && (x >= (y - 400) + 430 && x <= (y - 400) + 434))
                my_mlx_pixel_put(vars->img, x, y, vars->color_start);
            // r
            if ((y >= 380 && y <= 384) && (x >= 450 && x <= 480))
                my_mlx_pixel_put(vars->img, x, y, vars->color_start);
            if ((y >= 380 && y <= 416) && (x >= 463 && x <= 467))
                my_mlx_pixel_put(vars->img, x, y, vars->color_start);
            // t   
        }
    }
}