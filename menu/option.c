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

void	option(t_vars* vars)
{
	mlx_string_put(vars->mlx, vars->win, 382, 102, 0x000000, "Mandelbrot");
	mlx_string_put(vars->mlx, vars->win, 380, 100, vars->selectM, "Mandelbrot");
	mlx_string_put(vars->mlx, vars->win, 382, 152, 0x000000, "Julia Move");
	mlx_string_put(vars->mlx, vars->win, 380, 150, vars->selectJM, "Julia Move");
	mlx_string_put(vars->mlx, vars->win, 382, 202, 0x000000, "Burning Ship");
	mlx_string_put(vars->mlx, vars->win, 380, 200, vars->selectB, "Burning Ship");
	mlx_string_put(vars->mlx, vars->win, 382, 252, 0x000000, "Spong Menger");
	mlx_string_put(vars->mlx, vars->win, 380, 250, vars->selectS, "Spong Menger");
	mlx_string_put(vars->mlx, vars->win, 382, 302, 0x000000, "Dragon Curve");
	mlx_string_put(vars->mlx, vars->win, 380, 300, vars->selectD, "Dragon Curve");
	mlx_string_put(vars->mlx, vars->win, 382, 352, 0x000000, "Buddhabrot");
	mlx_string_put(vars->mlx, vars->win, 380, 350, vars->selectBD, "Buddhabrot");
	mlx_string_put(vars->mlx, vars->win, 382, 402, 0x000000, "Buddhabrot 2");
	mlx_string_put(vars->mlx, vars->win, 380, 400, vars->selectBDC, "Buddhabrot 2");
	mlx_string_put(vars->mlx, vars->win, 382, 452, 0x000000, "Mandelbrot Z Puissance N");
	mlx_string_put(vars->mlx, vars->win, 380, 450, vars->selectMP, "Mandelbrot Z Puissance N");
	mlx_string_put(vars->mlx, vars->win, 382, 502, 0x000000, "Buddhabrot Animation");
	mlx_string_put(vars->mlx, vars->win, 380, 500, vars->selectBA, "Buddhabrot Animation");
	mlx_string_put(vars->mlx, vars->win, 382, 552, 0x000000, "Mandelbrot Zoom");
	mlx_string_put(vars->mlx, vars->win, 380, 550, vars->selectMZ, "Mandelbrot Zoom");
}
