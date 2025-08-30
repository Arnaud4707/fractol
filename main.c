/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amugisha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 14:45:54 by amugisha          #+#    #+#             */
/*   Updated: 2025/01/07 22:33:26 by amugisha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx/mlx.h"
#include "include/header.h"

void	event(t_vars *vars)
{
	mlx_hook(vars->win, 17, 0, closey, vars);
	mlx_hook(vars->win, 2, 1L << 0, key, vars);
	mlx_mouse_hook(vars->win, zoom, vars);
	mlx_hook(vars->win, 6, 1L << 6, move, vars);
}

int init_img(t_vars* vars)
{
	vars->img = malloc(sizeof(t_data));
	if (!vars->img)
		return (-1);
	vars->img->img = mlx_new_image(vars->mlx, vars->largeur, vars->hauteur);
	if (!vars->img->img)
		return (-1);
	vars->img->addr = mlx_get_data_addr(vars->img->img,
			&vars->img->bits_per_pixel, &vars->img->line_length,
			&vars->img->endian);
	return (0);
}

int	init(int arg, char **argv, t_vars *vars)
{
	int	error;
	vars->zoomm = 1.0;
	vars->offsetX = 0.0;
	vars->offsetY = 0.0;
	vars->hue_shift = 0.00;
 	(void)error;
 	(void)arg;
 	(void)argv;
	error = check_arg(arg, argv, vars);
	if (error != 0)
	{
		errors(error, vars);
		return (-1);
	}
	vars->mlx = mlx_init();
	if (!vars->mlx)
		return (-1);
	vars->win = mlx_new_window(vars->mlx,
			vars->largeur, vars->hauteur, vars->name);
	if (!vars->win)
		return (-1);
	if (init_img(vars))
		return (-1);
	return (0);
}

int	main(int arg, char **argv)
{
	t_vars	vars;

	if (init(arg, argv, &vars) != 0)
		return (0);
	event(&vars);
	mlx_loop_hook(vars.mlx, loop_hook_master, &vars);
	mlx_loop(vars.mlx);
	return (0);
}
