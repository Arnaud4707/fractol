/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_d.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amugisha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 03:21:35 by amugisha          #+#    #+#             */
/*   Updated: 2025/01/06 04:44:05 by amugisha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include <math.h>
#include <stdlib.h>

void	colord_Buddhabrot(t_vars* vars, int x, int y)
{
	my_mlx_pixel_put(vars->img, x, y, (vars->color << 16) | (vars->color << 8) | vars->color);
}

void	colord_Buddhabrot_r(t_vars* vars, int x, int y)
{
	my_mlx_pixel_put(vars->img, x, y, (vars->color << 16));
}

void	colord_Buddhabrot_g(t_vars* vars, int x, int y)
{
	my_mlx_pixel_put(vars->img, x, y, (vars->color << 8));
}

void	colord_Buddhabrot_b(t_vars* vars, int x, int y)
{
	my_mlx_pixel_put(vars->img, x, y, vars->color);
}

void	colord_Buddhabrot_y(t_vars* vars, int x, int y)
{
	my_mlx_pixel_put(vars->img, x, y, (vars->color << 16) | (vars->color << 8));
}

void	colord_Buddhabrot_c(t_vars* vars, int x, int y)
{
	my_mlx_pixel_put(vars->img, x, y, (vars->color << 8) | vars->color);
}

void	colord_Buddhabrot_p(t_vars* vars, int x, int y)
{
	my_mlx_pixel_put(vars->img, x, y, (vars->color << 16) | vars->color);
}

void	colord_Buddhabrot_fire(t_vars* vars, int x, int y, double norm)
{
	int color = palette_fire(norm);
	my_mlx_pixel_put(vars->img, x, y, color);
}

void	colord_Buddhabrot_linear(t_vars* vars, int x, int y, double norm)
{
	int color = palette_linear(norm);
	my_mlx_pixel_put(vars->img, x, y, color);
}

void	colord_Buddhabrot_test(t_vars* vars, int x, int y, double norm)
{
	int color = palette_test(norm);
	my_mlx_pixel_put(vars->img, x, y, color);
}

void	prepare_color_buddhabrot(t_vars* vars, int x, int y, double norm)
{
	(void)norm;
	if (vars->key == 32)
		colord_Buddhabrot(vars, x, y);
	else if (vars->key == 114)
		colord_Buddhabrot_r(vars, x, y);
	else if (vars->key == 103)
		colord_Buddhabrot_g(vars, x, y);
	else if (vars->key == 98)
		colord_Buddhabrot_b(vars, x, y);
	else if (vars->key == 121)
		colord_Buddhabrot_y(vars, x, y);
	else if (vars->key == 99)
		colord_Buddhabrot_c(vars, x, y);
	else if (vars->key == 112)
		colord_Buddhabrot_p(vars, x, y);
	else if (vars->key == 65436)
		colord_Buddhabrot_fire(vars, x, y, norm);
	else if (vars->key == 65435)
		colord_Buddhabrot_linear(vars, x, y, norm);
	else if (vars->key == 65433)
		colord_Buddhabrot_test(vars, x, y, norm);
}