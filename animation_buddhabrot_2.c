/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation_buddhabrot_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amugisha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 16:35:22 by amugisha          #+#    #+#             */
/*   Updated: 2025/01/06 21:27:25 by amugisha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx/mlx.h"
#include "header.h"

int	loop_hook_buddhabrot_thread_2(void *arg)
{
    t_vars *vars = (t_vars *)arg;

    buddhabrot_colored_thread_animation_2(vars);
    mlx_put_image_to_window(vars->mlx, vars->win, vars->img->img, 0, 0);
    // limiter la vitesse (optionnel) : ~30 FPS -> 33ms = 33000us
    usleep(1000);
    // usleep(330);

    return 0;
}

void    hsv_to_rgb(double h, double s, double v, int *r, int *g, int *b)
{
    double c = v * s;
    double x = c * (1 - fabs(fmod(h / 60.0, 2) - 1));
    double m = v - c;

    double r_, g_, b_;
    if (h < 60)       { r_ = c; g_ = x; b_ = 0; }
    else if (h < 120) { r_ = x; g_ = c; b_ = 0; }
    else if (h < 180) { r_ = 0; g_ = c; b_ = x; }
    else if (h < 240) { r_ = 0; g_ = x; b_ = c; }
    else if (h < 300) { r_ = x; g_ = 0; b_ = c; }
    else              { r_ = c; g_ = 0; b_ = x; }

    *r = (int)((r_ + m) * 255);
    *g = (int)((g_ + m) * 255);
    *b = (int)((b_ + m) * 255);
}

void	buddhabrot_colored_thread_animation_2(t_vars *vars)
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
    rotate_image_90_clockwise(vars);

    hue_shift += 0.5;
    if (hue_shift >= 360.0)
    {
        hue_shift -= 360.0;
        vars->zoomm = 1;
    }
	vars->zoomm *= -1.01;
}


