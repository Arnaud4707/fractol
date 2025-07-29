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
		vars->ymin = tmp_min - (fabs((tmp_min - tmp_max) / 2) / 5);
		vars->ymax = tmp_max - (fabs((tmp_min - tmp_max) / 2) / 5);
	}
	else if (keycode == 65364)
	{
		vars->ymin = tmp_min + (fabs((tmp_min - tmp_max) / 2) / 5);
		vars->ymax = tmp_max + (fabs((tmp_min - tmp_max) / 2) / 5);
	}
}
