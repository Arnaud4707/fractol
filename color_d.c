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

int palette_fire(double t)
{
    int r;
    int g;
    int b;

	r = (int)(255 * fmin(1.0, t * 3.0));
	g = (int)(255 * fmin(1.0, fmax(0.0, t * 3.0 - 1.0)));
	b = (int)(255 * fmax(0.0, t * 3.0 - 2.0));
    return (r << 16) | (g << 8) | b;
}

int palette_linear(double norm)
{
    // exemple : noir → bleu → cyan → blanc
    int r, g, b;
    if (norm < 0.5) {
        double t = norm / 0.5;
        r = 0;
        g = (int)(t * 255);
        b = 128 + (int)(t * 127);
    } else {
        double t = (norm - 0.5) / 0.5;
        r = (int)(t * 255);
        g = 255;
        b = 255;
    }
    return (r << 16) | (g << 8) | b;
}

int palette_test(double norm)
{
    int r, g, b;
    if (norm < 0.5) {
        double t = norm / 0.5;
        r = 50 + (int)(t * 127);
        g = (int)(t * 255);
        b = 0;
    } else {
        double t = (norm - 0.5) / 0.5;
        r = 255;
        g = 255;
        b = (int)(t * 255);
    }
    return (r << 16) | (g << 8) | b;
}

void	color_buddhabrot_colored_p(t_vars* vars, int *accumR_global, int *accumG_global, int *accumB_global)
{
	int maxR = 0, maxG = 0, maxB = 0;
    for (int i = 0; i < WIDTH * HEIGHT; i++) {
        if (accumR_global[i] > maxR) maxR = accumR_global[i];
        if (accumG_global[i] > maxG) maxG = accumG_global[i];
        if (accumB_global[i] > maxB) maxB = accumB_global[i];
    }

    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            int idx = y * WIDTH + x;

            int r = (int)(255.0 * sqrt((double)accumR_global[idx] / (maxR ? maxR : 1)));
            int g = (int)(255.0 * sqrt((double)accumG_global[idx] / (maxG ? maxG : 1)));
            int b = (int)(255.0 * sqrt((double)accumB_global[idx] / (maxB ? maxB : 1)));

            // Mélange custom (comme ton code)
            int red   = (r * 0.8 + b * 0.4);
            int green = (g * 0.5 + r * 0.2);
            int blue  = (b * 1.0 + r * 0.3);

            if (red > 255) red = 255;
            if (green > 255) green = 255;
            if (blue > 255) blue = 255;

            int color = (red << 16) | (green << 8) | blue;
            my_mlx_pixel_put(vars->img, x, y, color);
        }
	}
}

void	color_buddhabrot_colored(t_vars* vars, int *accumR_global, int *accumG_global, int *accumB_global)
{
	int maxR = 0, maxG = 0, maxB = 0;
    for (int i = 0; i < WIDTH * HEIGHT; i++) {
        if (accumR_global[i] > maxR) maxR = accumR_global[i];
        if (accumG_global[i] > maxG) maxG = accumG_global[i];
        if (accumB_global[i] > maxB) maxB = accumB_global[i];
    }

    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            int idx = y * (int)WIDTH + x;
            int r = (maxR > 0) ? (int)(255.0 * sqrt((double)accumR_global[idx] / maxR)) : 0;
            int g = (maxG > 0) ? (int)(255.0 * sqrt((double)accumG_global[idx] / maxG)) : 0;
            int b = (maxB > 0) ? (int)(255.0 * sqrt((double)accumB_global[idx] / maxB)) : 0;

            int color = (r << 16) | (g << 8) | b;
            my_mlx_pixel_put(vars->img, x, y, color);
        }
    }
}

void	color_buddhabrot_colored_3(t_vars* vars, int *accumR_global, int *accumG_global, int *accumB_global)
{
	int maxR = 0, maxG = 0, maxB = 0;
    for (int i = 0; i < WIDTH * HEIGHT; i++) {
        if (accumR_global[i] > maxR) maxR = accumR_global[i];
        if (accumG_global[i] > maxG) maxG = accumG_global[i];
        if (accumB_global[i] > maxB) maxB = accumB_global[i];
    }

    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            int idx = y * WIDTH + x;

            int r = (maxR > 0) ? (int)(255.0 * sqrt((double)accumR_global[idx] / maxR)) : 0;
            int g = (maxG > 0) ? (int)(255.0 * sqrt((double)accumG_global[idx] / maxG)) : 0;
            int b = (maxB > 0) ? (int)(255.0 * sqrt((double)accumB_global[idx] / maxB)) : 0;

            int red   = (r * cos(vars->hue_shift) + g * sin(vars->hue_shift));
            int green = (g * cos(vars->hue_shift) + b * sin(vars->hue_shift));
            int blue  = (b * cos(vars->hue_shift) + r * sin(vars->hue_shift));

            if (red > 255) red = 255; if (red < 0) red = 0;
            if (green > 255) green = 255; if (green < 0) green = 0;
            if (blue > 255) blue = 255; if (blue < 0) blue = 0;

            int color = (red << 16) | (green << 8) | blue;
            my_mlx_pixel_put(vars->img, x, y, color);
        }
    }
}

void	color_buddhabrot_animation_2(t_vars* vars, int *accumR_global, int *accumG_global, int *accumB_global)
{
	int maxR = 0, maxG = 0, maxB = 0;
    for (int i = 0; i < WIDTH * HEIGHT; i++) {
        if (accumR_global[i] > maxR) maxR = accumR_global[i];
        if (accumG_global[i] > maxG) maxG = accumG_global[i];
        if (accumB_global[i] > maxB) maxB = accumB_global[i];
    }

    static double hue_shift = 0.0;

    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            int idx = y * WIDTH + x;

            double intensity = sqrt(
                (double)accumR_global[idx] / (maxR ? maxR : 1) +
                (double)accumG_global[idx] / (maxG ? maxG : 1) +
                (double)accumB_global[idx] / (maxB ? maxB : 1)
            );
            double h = fmod(hue_shift + intensity * 360.0, 360.0);
            double s = 1.0;
            double v = intensity > 1.0 ? 1.0 : intensity;

            int r,g,b;
            hsv_to_rgb(h, s, v, &r, &g, &b);

            int color = (r << 16) | (g << 8) | b;
            my_mlx_pixel_put(vars->img, x, y, color);
        }
    }
    hue_shift += 0.5;
    if (hue_shift >= 360.0) hue_shift -= 360.0;
}

void	prepare_color_buddhabrot_thread(t_vars* vars, int *accumR_global, int *accumG_global, int *accumB_global)
{
	if (vars->key == 32)
		color_buddhabrot_colored(vars, accumR_global, accumG_global, accumB_global);
    else if (vars->key == 65436)
        color_buddhabrot_colored_p(vars, accumR_global, accumG_global, accumB_global);
    else if (vars->key == 65433)
        color_buddhabrot_colored_3(vars, accumR_global, accumG_global, accumB_global);
}
