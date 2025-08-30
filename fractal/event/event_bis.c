/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amugisha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 16:26:27 by amugisha          #+#    #+#             */
/*   Updated: 2025/01/07 19:58:27 by amugisha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx/mlx.h"
#include "../../include/header.h"

void	fractal_simple(int keycode, t_vars *vars)
{
	if (keycode == 65361 || keycode == 65363
		|| keycode == 65362 || keycode == 65364)
		arrow(keycode, vars);
	else if (keycode == 115)
		vars->play = 0;
	else if (keycode == 112)
		vars->play = 1;
	else if (keycode == 114 || keycode == 121 || keycode == 103
		|| keycode == 98 || keycode == 65436
		|| keycode == 65433 || keycode == 65435
		|| keycode == 32 || keycode == 65430
		|| keycode == 65437)
		set_color(keycode, vars);
}

void	fractal_not_simple(int keycode, t_vars *vars)
{
	if (vars->current_key != keycode && (keycode == 114 || keycode == 99 || keycode == 103
		|| keycode == 98 || keycode == 112 || keycode == 121 || keycode == 32
		|| keycode == 65436 || keycode == 65433 || keycode == 65435 || keycode == 65430) && vars->f == 7)
		set_color(keycode, vars);
	else if (vars->current_key != keycode && (keycode == 32 || keycode == 65436) && vars->f == 9)
		set_color(keycode, vars);
	else if ((keycode == 114 || keycode == 121 || keycode == 103
		|| keycode == 98 || keycode == 65436
		|| keycode == 65433 || keycode == 65435
		|| keycode == 32 || keycode == 65430
		|| keycode == 65437) && (vars->f == 10 || vars->f == 8))
		palette_color(keycode, vars);
}

int	key(int keycode, t_vars *vars)
{
	(void)vars;
	if (keycode == 65307)
		closey(vars);
	vars->key = keycode;
	if (vars->f == 1 || vars->f == 2 || vars->f == 3 || vars->f == 4 || vars->f == 5)
		fractal_simple(keycode, vars);
	else
		fractal_not_simple(keycode, vars);
	printf("%d\n", keycode);
	return (0);
}
