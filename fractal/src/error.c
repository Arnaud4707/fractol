/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amugisha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 22:23:51 by amugisha          #+#    #+#             */
/*   Updated: 2025/01/11 01:12:55 by amugisha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/header.h"

void	errors(int error, t_vars *vars)
{
	(void)vars;
	if (error == -1)
	{
		write(1, "./fractol Dragon\n", 17);
		write(1, "./fractol Buddhabrot\n", 21);
		write(1, "./fractol BuddhabrotA\n", 22);
		write(1, "./fractol BuddhabrotA2\n", 23);
		write(1, "./fractol Buddhabrot2\n", 22);
		write(1, "./fractol BurningShip\n", 22);
		write(1, "./fractol Mandelbrot\n", 22);
		write(1, "./fractol MandelbrotA\n", 22);
		write(1, "./fractol SpongMenger x[int] limite [1;639]\n", 45);
		write(1, "./fractol Mandelbrot_zoom\n", 25);
		write(1, "./fractol Mandelbrot\n", 21);
		write(1, "./fractol Julia x[double]", 25);
		write(1, " y[double] limite[-1.5;1.5]\n", 28);
		write(1, "./fractol JuliaMove \n", 21);
	}
	else if (error == -2)
		write(1, "Probleme de malloc\n", 19);
}

int	ckeck(char *s, int l)
{
	if (l == 1)
	{
		if (len(s) != 10)
			return (-1);
	}
	else if (l == 2)
	{
		if (len(s) != 5)
			return (-1);
	}
	else if (l == 3)
	{
		if (len(s) != 9)
			return (-1);
	}
	else if (l == 4)
	{
		if (len(s) != 11)
			return (-1);
	}
	else if (l == 5)
	{
		if (len(s) != 6)
			return (-1);
	}
	else if (l == 6)
	{
		if (len(s) != 12)
			return (-1);
	}
	else if (l == 7)
	{
		if (len(s) != 10)
			return (-1);
	}
	else if (l == 8)
	{
		if (len(s) != 15)
			return (-1);
	}
	else if (l == 9)
	{
		if (len(s) != 11)
			return (-1);
	}
	else if (l == 10)
	{
		if (len(s) != 11)
			return (-1);
	}
	else if (l == 11)
	{
		if (len(s) != 11)
			return (-1);
	}
	else if (l == 12)
	{
		if (len(s) != 11)
			return (-1);
	}
	return (0);
}
