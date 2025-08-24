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
	mlx_hook(vars->win, 6, 1L << 6, julia_move, vars);
	mlx_hook(vars->win,  6, 1L << 6, event_button, vars);
}

int	init(int arg, char **argv, t_vars *vars)
{
	int	error;
	// usleep(10000000);
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

int	main(int arg, char **argv)
{
	t_vars	vars;

	// usleep(10000000);
	if (init(arg, argv, &vars) != 0)
		return (0);
	if (vars.f == -1)
		menu(&vars);
	if (vars.f == 1)
		fractal(&vars, calcule_m);
	else if (vars.f == 2 || vars.f == 3)
		fractal(&vars, calcule_j);
	else if (vars.f == 4)
		fractal(&vars, calcule_b);
	else if (vars.f == 7)
		buddhabrot_thread(&vars);
	else if (vars.f == 9)
		buddhabrot_colored_thread(&vars);
	else if (vars.f == 5)
		calcule_dragon(&vars);
	else if (vars.f == 12)
		drawMenger2D(&vars, vars.max_iteration);
	mlx_put_image_to_window(vars.mlx, vars.win, vars.img->img, 0, 0);
	if (vars.f == 11)
		mlx_loop_hook(vars.mlx, loop_hook_buddhabrot_thread, &vars);
	else if (vars.f == 10)
		mlx_loop_hook(vars.mlx, loop_hook_mandelbrot_pussance_n, &vars);
	else if (vars.f == 8)
		mlx_loop_hook(vars.mlx, loop_hook_zoom_mandelbrot, &vars);
	else if (vars.f == 6)
		mlx_loop_hook(vars.mlx, loop_hook_buddhabrot_thread_2, &vars);
	event(&vars);
	mlx_loop(vars.mlx);
	return (0);
}
