/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zoom.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amugisha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 02:52:52 by amugisha          #+#    #+#             */
/*   Updated: 2025/01/07 23:07:41 by amugisha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx/mlx.h"
#include "header.h"

void	function_asymptote_click(int button, double x, double y, t_vars *vars)
{
	double	tmp_min;
	double	tmp_max;

	if (button == 1)
	{
		tmp_min = vars->xmin;
		tmp_max = vars->xmax;
		vars->xmin = tmp_min + (x * 0.9);
		vars->xmax = tmp_max - ((tmp_max - tmp_min - x) * 0.9);
		tmp_min = vars->ymin;
		tmp_max = vars->ymax;
		vars->ymin = tmp_min + (y * 0.9);
		vars->ymax = tmp_max - ((tmp_max - tmp_min - y) * 0.9);
	}
	else
	{
		tmp_min = vars->xmin;
		tmp_max = vars->xmax;
		vars->xmin = tmp_min - (x * 9);
		vars->xmax = tmp_max + ((tmp_max - tmp_min - x) * 9);
		tmp_min = vars->ymin;
		tmp_max = vars->ymax;
		vars->ymin = tmp_min - (y * 9);
		vars->ymax = tmp_max + ((tmp_max - tmp_min - y) * 9);
	}
}

void	function_asymptote(int button, double x, double y, t_vars *vars)
{
	double	tmp_min;
	double	tmp_max;

	if (button == 4)
	{
		tmp_min = vars->xmin;
		tmp_max = vars->xmax;
		vars->xmin = tmp_min + (x / 10);
		vars->xmax = tmp_max - ((tmp_max - tmp_min - x) / 10);
		tmp_min = vars->ymin;
		tmp_max = vars->ymax;
		vars->ymin = tmp_min + (y / 10);
		vars->ymax = tmp_max - ((tmp_max - tmp_min - y) / 10);
	}
	else
	{
		tmp_min = vars->xmin;
		tmp_max = vars->xmax;
		vars->xmin = tmp_min - (x / 10);
		vars->xmax = tmp_max + ((tmp_max - tmp_min - x) / 10);
		tmp_min = vars->ymin;
		tmp_max = vars->ymax;
		vars->ymin = tmp_min - (y / 10);
		vars->ymax = tmp_max + ((tmp_max - tmp_min - y) / 10);
	}
}

void	iteration(int button, t_vars *vars)
{
	(void)button;
	if (vars->max_iteration > 1000)
	{
		vars->max_iteration = 1000;
		vars->zoom_i++;
	}
	if (vars->max_iteration < 1000 && vars->zoom_i > 0)
	{
		vars->max_iteration = 1000;
		vars->zoom_i--;
	}
	if (vars->max_iteration < 50)
		vars->max_iteration = 50;
}

void	action_zoom(int button, double tmpx, double tmpy, t_vars *vars)
{
	if (button == 4)
	{
		vars->max_iteration = vars->max_iteration + (vars->max_iteration / 50);
		iteration(button, vars);
		function_asymptote(button, tmpx, tmpy, vars);
	}
	else if (button == 5)
	{
		vars->max_iteration = vars->max_iteration - (vars->max_iteration / 50);
		iteration(button, vars);
		function_asymptote(button, tmpx, tmpy, vars);
	}
	else if (button == 1)
	{
		vars->max_iteration = vars->max_iteration + (vars->max_iteration / 2);
		iteration(button, vars);
		function_asymptote_click(button, tmpx, tmpy, vars);
	}
	else if (button == 3)
	{
		vars->max_iteration = vars->max_iteration - (vars->max_iteration / 2);
		iteration(button, vars);
		function_asymptote_click(button, tmpx, tmpy, vars);
	}
}
