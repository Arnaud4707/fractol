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

void	fractal(t_vars *vars, void (*calcule)(t_vars *, int, int))
{
	int	x;
	int	y;

	vars->ix = vars->largeur / (vars->xmax - vars->xmin);
	vars->iy = vars->hauteur / (vars->ymax - vars->ymin);
	y = 0;
	while (y < vars->hauteur)
	{
		x = 0;
		while (x < vars->largeur)
		{
			calcule(vars, x, y);
			x++;
		}
		y++;
	}
}