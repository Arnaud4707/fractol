/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amugisha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 00:28:57 by amugisha          #+#    #+#             */
/*   Updated: 2025/01/07 22:32:41 by amugisha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx/mlx.h"
#include "header.h"
#include <unistd.h>
#include <math.h>

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	len(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

double	gamma_correct(double value)
{
	double	gamma;

	gamma = 2.2;
	return (pow(value, 1.0 / gamma));
}

void	horizontal(int keycode, t_vars *vars)
{
	double	tmp_min;
	double	tmp_max;

	tmp_min = vars->xmin;
	tmp_max = vars->xmax;
	if (keycode == 65361)
	{
		vars->xmin = tmp_min - (fabs((tmp_min - tmp_max) / 2) / 5);
		vars->xmax = tmp_max - (fabs((tmp_min - tmp_max) / 2) / 5);
	}
	else if (keycode == 65363)
	{
		vars->xmin = tmp_min + (fabs((tmp_min - tmp_max) / 2) / 5);
		vars->xmax = tmp_max + (fabs((tmp_min - tmp_max) / 2) / 5);
	}
}

void	vertical(int keycode, t_vars *vars)
{
	double	tmp_min;
	double	tmp_max;

	tmp_min = vars->ymin;
	tmp_max = vars->ymax;

	if (keycode == 65362)
	{
		if (vars->f == 5 && vars->ymax <= 51.0)
		{}
		else
		{
			vars->ymin = tmp_min - (fabs((tmp_min - tmp_max) / 2) / 5);
			vars->ymax = tmp_max - (fabs((tmp_min - tmp_max) / 2) / 5);
		}
	}
	else if (keycode == 65364)
	{
		if (vars->f == 5 && vars->ymin > 820.0)
		{}
		else
		{
			vars->ymin = tmp_min + (fabs((tmp_min - tmp_max) / 2) / 5);
			vars->ymax = tmp_max + (fabs((tmp_min - tmp_max) / 2) / 5);
		}
	}
}

void	rotate_image_90_clockwise(t_vars *vars)
{
    int w = vars->largeur;
    int h = vars->hauteur;

    // Créer une nouvelle image avec largeur et hauteur inversées
    t_data *new_img = malloc(sizeof(t_data));
    new_img->img = mlx_new_image(vars->mlx, h, w);
    new_img->addr = mlx_get_data_addr(new_img->img, &new_img->bits_per_pixel, &new_img->line_length, &new_img->endian);

    char *src = vars->img->addr;
    char *dst = new_img->addr;

    for (int y = 0; y < h; y++)
    {
        for (int x = 0; x < w; x++)
        {
            // Lire la couleur du pixel original
            int src_pixel = *(int *)(src + y * vars->img->line_length + x * (vars->img->bits_per_pixel / 8));

            // Nouvelle position (x', y') pour rotation horaire
            int new_x = h - 1 - y;
            int new_y = x;

            // Écrire dans la nouvelle image
            *(int *)(dst + new_y * new_img->line_length + new_x * (new_img->bits_per_pixel / 8)) = src_pixel;
        }
    }

    // Supprimer l'ancienne image et remplacer par la nouvelle
    mlx_destroy_image(vars->mlx, vars->img->img);
    free(vars->img);
    vars->img = new_img;

    // Échanger largeur et hauteur
    vars->largeur = h;
    vars->hauteur = w;
}
