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

#include "header.h"
#include <math.h>

int	precalculate_colors_1(t_vars *vars)
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
		return (-1);
	while (i < (int)vars->max_iteration)
	{
		vars->palette[i] = (i * 5) % 256 << 16
			| (i * 7) % 256 << 8 | (i * 11) % 256;
		i++;
	}
	return (0);
}

int	precalculate_colors_2(t_vars *vars)
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
		return (-1);
	while (i < (int)vars->max_iteration)
	{
		vars->palette[i] = (i * 25) % 256 << 16
			| (i * 25) % 256 << 8 | (i * 5) % 256;
		i++;
	}
	return (0);
}

int	precalculate_colors_3(t_vars *vars)
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
		return (-1);
	while (i < (int)vars->max_iteration)
	{
		vars->palette[i] = (i * 5) % 256 << 16
			| (i * 25) % 256 << 8
			| (i * 25) % 256;
		i++;
	}
	return (0);
}

int	precalculate_colors_4(t_vars *vars)
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
		return (-1);
	while (i < (int)vars->max_iteration)
	{
		vars->palette[i] = (i * 15) % 256 << 16
			| (i * 30) % 256 << 8
			| (i * 45) % 256;
		i++;
	}
	return (0);
}

int	precalculate_colors_5(t_vars *vars)
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
		return (-1);
	while (i < (int)vars->max_iteration)
	{
		vars->palette[i] = (i * 7) % 255 << 16
			| (i * 23) % 255 << 8
			| (i * 55) % 255;
		i++;
	}
	return (0);
}
