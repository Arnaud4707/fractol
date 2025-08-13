/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amugisha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 04:46:06 by amugisha          #+#    #+#             */
/*   Updated: 2025/01/11 01:00:02 by amugisha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include <math.h>
#include <stdlib.h>

int	precalculate_colors(t_vars *vars)
{
	int		i;
	double	t;

	i = 0;
	if (vars->palette)
	{
		free(vars->palette);
		vars->palette = NULL;
	}
	if (vars->max_iteration > 1000)
		vars->max_iteration = 1000;
	vars->palette = (int *) malloc (1000 * sizeof(int));
	if (!vars->palette)
		return (-2);
	while (i < (int)vars->max_iteration)
	{
		t = (double)i / vars->max_iteration;
		vars->palette[i] = (int)(gamma_correct(9 * (1 - t) * t * t * t)
				* 255) << 16
			| (int)(gamma_correct(15 * (1 - t) * (1 - t) * t * t) * 255) << 8
			| (int)(gamma_correct(8.5 * (1 - t) * (1 - t) * (1 - t) * t) * 255);
		i++;
	}
	return (0);
}

int	precalculate_colors_g(t_vars *vars)
{
	int	i;

	i = 0;
	if (vars->palette)
	{
		free(vars->palette);
		vars->palette = NULL;
	}
	vars->palette = (int *) malloc (1000 * sizeof(int));
	if (!vars->palette)
		return (-2);
	while (i < (int)vars->max_iteration)
	{
		vars->palette[i] = 0 << 16 | (i * 15) % 256 << 8 | 0;
		i++;
	}
	return (0);
}

int	precalculate_colors_r(t_vars *vars)
{
	int	i;

	i = 0;
	if (vars->palette)
	{
		free(vars->palette);
		vars->palette = NULL;
	}
	vars->palette = (int *) malloc (1000 * sizeof(int));
	if (!vars->palette)
		return (-2);
	while (i < (int)vars->max_iteration)
	{
		vars->palette[i] = (i * 5) % 256 << 16
			| 0 << 8
			| 0;
		i++;
	}
	return (0);
}

int	precalculate_colors_b(t_vars *vars)
{
	int	i;

	i = 0;
	if (vars->palette)
	{
		free(vars->palette);
		vars->palette = NULL;
	}
	vars->palette = (int *) malloc (1000 * sizeof(int));
	if (!vars->palette)
		return (-2);
	while (i < (int)vars->max_iteration)
	{
		vars->palette[i] = 0 << 16
			| 0 << 8
			| (i * 15) % 256;
		i++;
	}
	return (0);
}

int	precalculate_colors_y(t_vars *vars)
{
	int	i;

	i = 0;
	if (vars->palette)
	{
		free(vars->palette);
		vars->palette = NULL;
	}
	vars->palette = (int *) malloc (1000 * sizeof(int));
	if (!vars->palette)
		return (-2);
	while (i < (int)vars->max_iteration)
	{
		vars->palette[i] = (i * 15) % 256 << 16
			| (i * 15) % 256 << 8
			| 0;
		i++;
	}
	return (0);
}
