/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intro.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amugisha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 14:45:54 by amugisha          #+#    #+#             */
/*   Updated: 2025/01/07 22:33:26 by amugisha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx/mlx.h"
#include "include/header.h"

void	draw_wave(t_vars* vars)
{
	static double t = 0;
	
	for (int y = 0; y < vars->hauteur; y += 10)
	{
		for (int x = 0; x < vars->largeur; x += 10)
		{
			double cx = vars->largeur / 2.0;
			double cy = vars->hauteur / 2.0;
			double dx = x - cx;
			double dy = y - cy;
			double dist = sqrt(dx*dx + dy*dy);
			double wave = (10.0 + 80.0 * vars->audio_amp) * sin(0.05 * dist - t);

			int newY = (int)(y + wave);
			if (newY >= 0 && newY < vars->hauteur)
				my_mlx_pixel_put(vars->img, x, newY, 0xFFFFFF);
		}
	}
	t += 0.1;
}