/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation_buddhabrot.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amugisha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 16:35:22 by amugisha          #+#    #+#             */
/*   Updated: 2025/01/06 21:27:25 by amugisha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx/mlx.h"
#include "header.h"

int	loop_hook_buddhabrot_thread(void *arg)
{
    t_vars *vars = (t_vars *)arg;

    buddhabrot_colored_thread_animation_2(vars);
    mlx_put_image_to_window(vars->mlx, vars->win, vars->img->img, 0, 0);
    // limiter la vitesse (optionnel) : ~30 FPS -> 33ms = 33000us
    usleep(1000);
    // usleep(330);

    return 0;
}

void	*buddhabrot_colored_worker_animation(void *arg)
{
    ThreadDataColor *data = (ThreadDataColor *)arg;

    for (int s = 0; s < data->samples; s++) {
        // Coordonnées aléatoires dépendant du data->vars->zoomm/offset
        double cr = ((double)rand_r(&data->seed) / RAND_MAX) * 4.0 / data->vars->zoomm - 2.0/data->vars->zoomm + data->vars->offsetX;
        double ci = ((double)rand_r(&data->seed) / RAND_MAX) * 4.0 / data->vars->zoomm - 2.0/data->vars->zoomm + data->vars->offsetY;

        double zr = 0.0, zi = 0.0;
        double trajectory_x[MAX_ITER];
        double trajectory_y[MAX_ITER];

        int iter = 0, escaped = 0;

        while (iter < MAX_ITER) {
            double zr2 = zr*zr - zi*zi + cr;
            double zi2 = 2*zr*zi + ci;

            zr = zr2;
            zi = zi2;

            trajectory_x[iter] = zr;
            trajectory_y[iter] = zi;

            if ((zr*zr + zi*zi) > 4.0) {
                escaped = 1;
                break;
            }
            iter++;
        }

        if (escaped) {
            int channel;
            if (iter <= 20) channel = 2;
            else if (iter <= 200) channel = 1;
            else channel = 0;

            for (int j = 0; j < iter; j++) {
                int px = (int)((trajectory_x[j] + 2.0) / 4.0 * WIDTH);
                int py = (int)((trajectory_y[j] + 2.0) / 4.0 * HEIGHT);
                if (px >= 0 && px < WIDTH && py >= 0 && py < HEIGHT) {
                    int idx = py * WIDTH + px;
                    if (channel == 0) data->accumR[idx]++;
                    else if (channel == 1) data->accumG[idx]++;
                    else data->accumB[idx]++;
                }
            }
        }
    }
    return NULL;
}

void	buddhabrot_colored_thread_animation(t_vars *vars)
{
    static int *accumR_global = NULL;
    static int *accumG_global = NULL;
    static int *accumB_global = NULL;

    if (!accumR_global) {
        accumR_global = calloc(WIDTH * HEIGHT, sizeof(int));
        accumG_global = calloc(WIDTH * HEIGHT, sizeof(int));
        accumB_global = calloc(WIDTH * HEIGHT, sizeof(int));
    }

    pthread_t threads[THREADS];
    ThreadDataColor data[THREADS];

    for (int t = 0; t < THREADS; t++) {
        data[t].vars = vars;
        data[t].accumR = calloc(WIDTH * HEIGHT, sizeof(int));
        data[t].accumG = calloc(WIDTH * HEIGHT, sizeof(int));
        data[t].accumB = calloc(WIDTH * HEIGHT, sizeof(int));
        data[t].samples = SAMPLES / THREADS;
        data[t].seed = rand();
        pthread_create(&threads[t], NULL, buddhabrot_colored_worker_animation, &data[t]);
    }

    for (int t = 0; t < THREADS; t++) {
        pthread_join(threads[t], NULL);
        for (int i = 0; i < WIDTH * HEIGHT; i++) {
            accumR_global[i] += data[t].accumR[i];
            accumG_global[i] += data[t].accumG[i];
            accumB_global[i] += data[t].accumB[i];
        }
        free(data[t].accumR);
        free(data[t].accumG);
        free(data[t].accumB);
    }

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

            // // décalage de teinte simple
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

    // if (vars->zoomm < 15.0)
	//     vars->zoomm *= 1.1;
	// vars->hue_shift += 0.03;
	static int dir;
    // static int dir_h;

    if (dir == 0)
	{
		vars->hue_shift += 0.03; 
        vars->zoomm *= -1.05;
		if (vars->hue_shift > 1.7)
			dir = 1;
	}
	else
	{
		vars->hue_shift -= 0.03;
		vars->zoomm *= -0.95; 
		if (vars->hue_shift < -0.3)
			dir = 0;
	}
	// if (dir_h == 0)
	// {
	// 	vars->zoomm *= -1.05;         // vars->zoomm progressif
	// 	if (vars->zoomm > 7 || vars->zoomm < -7)
	// 		dir_h = 1;
	// }
	// else
	// {
        // 	vars->zoomm *= -0.95;         // vars->zoomm progressif
        // 	if (vars->zoomm < 0.01 && vars->zoomm > -0.01)
        // 	{
        // 		dir_h = 0;
        // 	}
	// }
    rotate_image_90_clockwise(vars);
}
