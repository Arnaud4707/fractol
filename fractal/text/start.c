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
                || (y >= 412 && y <= 416)) && (x >= 295 && x <= 315))
                my_mlx_pixel_put(vars->img, x, y, vars->color);
            if ((y >= 380 && y <= 400) && (x >= 295 && x <= 299))
                my_mlx_pixel_put(vars->img, x, y, vars->color);
            if ((y >= 400 && y <= 416) && (x >= 311 && x <= 315))
                my_mlx_pixel_put(vars->img, x, y, vars->color);
            // s
            if ((y >= 380 && y <= 384) && (x >= 330 && x <= 360))
                my_mlx_pixel_put(vars->img, x, y, vars->color);
            if ((y >= 380 && y <= 416) && (x >= 343 && x <= 347))
                my_mlx_pixel_put(vars->img, x, y, vars->color);
            // t
            if (((y >= 380 && y <= 384) || (y >= 396 && y <= 400))
                && (x >= 370 && x <= 390))
                my_mlx_pixel_put(vars->img, x, y, vars->color);
            if ((y >= 380 && y <= 416) && ((x >= 370 && x <= 374)
                || (x >= 386 && x <= 390)))
                my_mlx_pixel_put(vars->img, x, y, vars->color);
            // a
            // R
            // barre horizontale du haut
            if ((y >= 380 && y <= 384) && (x >= 400 && x <= 420))
                my_mlx_pixel_put(vars->img, x, y, vars->color);

            // barre verticale gauche
            if ((y >= 380 && y <= 416) && (x >= 400 && x <= 404))
                my_mlx_pixel_put(vars->img, x, y, vars->color);

            // barre horizontale du milieu
            if ((y >= 396 && y <= 400) && (x >= 400 && x <= 420))
                my_mlx_pixel_put(vars->img, x, y, vars->color);

            // barre verticale droite haute (pour fermer le "P")
            if ((y >= 380 && y <= 400) && (x >= 416 && x <= 420))
                my_mlx_pixel_put(vars->img, x, y, vars->color);

            // diagonale de la jambe du R
            if ((y >= 400 && y <= 416) && (x >= (y - 400) + 410 && x <= (y - 400) + 414))
                my_mlx_pixel_put(vars->img, x, y, vars->color);

            // r
            if ((y >= 380 && y <= 384) && (x >= 430 && x <= 460))
                my_mlx_pixel_put(vars->img, x, y, vars->color);
            if ((y >= 380 && y <= 416) && (x >= 443 && x <= 447))
                my_mlx_pixel_put(vars->img, x, y, vars->color);
            // t   
        }
    }
}