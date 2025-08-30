/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal_bis.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amugisha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 16:35:22 by amugisha          #+#    #+#             */
/*   Updated: 2025/01/06 21:27:25 by amugisha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx/mlx.h"
#include "../../include/header.h"

void *buddhabrot_colored_worker(void *arg)
{
    ThreadDataColor *data = (ThreadDataColor *)arg;

    for (int s = 0; s < data->samples; s++) {
        double cr = ((double)rand_r(&data->seed) / RAND_MAX) * 4.0 - 2.0;
        double ci = ((double)rand_r(&data->seed) / RAND_MAX) * 4.0 - 2.0;

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
            if (iter <= 20) channel = 2;      // bleu
            else if (iter <= 200) channel = 1; // vert
            else channel = 0;                 // rouge

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

void	buddhabrot_colored_thread(t_vars *vars)
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
        pthread_create(&threads[t], NULL, buddhabrot_colored_worker, &data[t]);
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

    prepare_color_buddhabrot_thread(vars, accumR_global, accumG_global, accumB_global);
    vars->current_key = vars->key;
    rotate_image_90_clockwise(vars);
}

void *buddhabrot_worker(void *arg)
{
    ThreadData *data = (ThreadData *)arg;
    int *accum = data->accum_local;

    for (int s = 0; s < data->samples; s++) {
        double cr = ((double)rand_r(&data->seed) / RAND_MAX) * 4.0 - 2.0;
        double ci = ((double)rand_r(&data->seed) / RAND_MAX) * 4.0 - 2.0;

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
            for (int j = 0; j < iter; j++) {
                int px = (int)((trajectory_x[j] + 2.0) / 4.0 * WIDTH);
                int py = (int)((trajectory_y[j] + 2.0) / 4.0 * HEIGHT);
                if (px >= 0 && px < WIDTH && py >= 0 && py < HEIGHT) {
                    accum[py * WIDTH + px]++;
                }
            }
        }
    }

    return NULL;
}

void	buddhabrot_thread(t_vars *vars)
{
    static int *accum_global = NULL;
    if (!accum_global)
        accum_global = calloc(WIDTH * HEIGHT, sizeof(int));

    pthread_t threads[THREADS];
    ThreadData data[THREADS];

    for (int t = 0; t < THREADS; t++) {
        data[t].vars = vars;
        data[t].accum_local = calloc(WIDTH * HEIGHT, sizeof(int));
        data[t].samples = SAMPLES / THREADS;
        data[t].seed = rand();
        pthread_create(&threads[t], NULL, buddhabrot_worker, &data[t]);
    }

    for (int t = 0; t < THREADS; t++) {
        pthread_join(threads[t], NULL);

        for (int i = 0; i < WIDTH * HEIGHT; i++) {
            accum_global[i] += data[t].accum_local[i];
        }
        free(data[t].accum_local);
    }

    int max_val = 0;
    for (int i = 0; i < WIDTH * HEIGHT; i++)
        if (accum_global[i] > max_val)
            max_val = accum_global[i];

    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
           int val = accum_global[y * WIDTH + x];
            double norm = (double)val / max_val;

            norm = pow(norm, 0.8); 
            int color = (int)(norm * 255.0 * 1.3);
            if (color > 255)
                color = 255;
            vars->color = color;
            prepare_color_buddhabrot(vars, x, y, norm);
        }
    }
    vars->current_key = vars->key;
    rotate_image_90_clockwise(vars);
}