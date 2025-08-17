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
#include "header.h"

void	buddhabrot_colored_p(t_vars *vars)
{
    static int *accum = NULL;
	static int *accumR = NULL;
	static int *accumG = NULL;
	static int *accumB = NULL;

	if (!accum)
			accum = calloc(WIDTH * HEIGHT, sizeof(int)); // tableau pour accumulation
	if (!accumR) {
		accumR = calloc(WIDTH * HEIGHT, sizeof(int));
		accumG = calloc(WIDTH * HEIGHT, sizeof(int));
		accumB = calloc(WIDTH * HEIGHT, sizeof(int));
	}

    for (int s = 0; s < SAMPLES; s++) {
        double cr = ((double)rand() / RAND_MAX) * 4.0 - 2.0; // [-2, 2]
        double ci = ((double)rand() / RAND_MAX) * 4.0 - 2.0; // [-2, 2]

        double zr = 0.0, zi = 0.0;
        double trajectory_x[MAX_ITER];
        double trajectory_y[MAX_ITER];

        int iter = 0;
        int escaped = 0;

        // Première passe : calcul et stockage de la trajectoire
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

        // Si diverge, on incrémente dans la matrice accumulation
        if (escaped) {
			// Choisir la couleur en fonction du nombre d'itérations
			int channel;
			if (iter <= 20) channel = 2;     // bleu
			else if (iter <= 200) channel = 1; // vert
			else channel = 0;                // rouge

			for (int j = 0; j < iter; j++) {
				int px = (int)((trajectory_x[j] + 2.0) / 4.0 * WIDTH);
				int py = (int)((trajectory_y[j] + 2.0) / 4.0 * HEIGHT);
				if (px >= 0 && px < WIDTH && py >= 0 && py < HEIGHT) {
					int idx = py * WIDTH + px;
					if (channel == 0) accumR[idx]++;
					else if (channel == 1) accumG[idx]++;
					else accumB[idx]++;
				}
			}
		}
    }

    int maxR = 0, maxG = 0, maxB = 0;
	for (int i = 0; i < WIDTH * HEIGHT; i++) {
		if (accumR[i] > maxR) maxR = accumR[i];
		if (accumG[i] > maxG) maxG = accumG[i];
		if (accumB[i] > maxB) maxB = accumB[i];
	}

	for (int y = 0; y < HEIGHT; y++) {
		for (int x = 0; x < WIDTH; x++) {
			int idx = y * WIDTH + x;

			// Normalisation (évite saturation brutale, on garde sqrt pour un effet doux)
			int r = (int)(255.0 * sqrt((double)accumR[idx] / (maxR ? maxR : 1)));
			int g = (int)(255.0 * sqrt((double)accumG[idx] / (maxG ? maxG : 1)));
			int b = (int)(255.0 * sqrt((double)accumB[idx] / (maxB ? maxB : 1)));

			// Mélange custom : on renforce certaines composantes
			int red   = (r * 0.8 + b * 0.4);   // rouge + un peu de bleu → rose
			int green = (g * 0.5 + r * 0.2);   // vert adouci → pastel
			int blue  = (b * 1.0 + r * 0.3);   // bleu saturé + un peu de rouge → violet/cyan

			// Clamp pour rester entre 0 et 255
			if (red > 255) red = 255;
			if (green > 255) green = 255;
			if (blue > 255) blue = 255;

			int color = (red << 16) | (green << 8) | blue;
			my_mlx_pixel_put(vars->img, x, y, color);
		}
	}
	rotate_image_90_clockwise(vars);
}

void	buddhabrot_colored(t_vars *vars)
{
    static int *accum = NULL;
	static int *accumR = NULL;
	static int *accumG = NULL;
	static int *accumB = NULL;

	if (!accum)
			accum = calloc(WIDTH * HEIGHT, sizeof(int)); // tableau pour accumulation
	if (!accumR) {
		accumR = calloc(WIDTH * HEIGHT, sizeof(int));
		accumG = calloc(WIDTH * HEIGHT, sizeof(int));
		accumB = calloc(WIDTH * HEIGHT, sizeof(int));
	}

    for (int s = 0; s < SAMPLES; s++) {
        double cr = ((double)rand() / RAND_MAX) * 4.0 - 2.0; // [-2, 2]
        double ci = ((double)rand() / RAND_MAX) * 4.0 - 2.0; // [-2, 2]

        double zr = 0.0, zi = 0.0;
        double trajectory_x[MAX_ITER];
        double trajectory_y[MAX_ITER];

        int iter = 0;
        int escaped = 0;

        // Première passe : calcul et stockage de la trajectoire
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

        // Si diverge, on incrémente dans la matrice accumulation
        if (escaped) {
			// Choisir la couleur en fonction du nombre d'itérations
			int channel;
			if (iter <= 20) channel = 2;     // bleu
			else if (iter <= 200) channel = 1; // vert
			else channel = 0;                // rouge

			for (int j = 0; j < iter; j++) {
				int px = (int)((trajectory_x[j] + 2.0) / 4.0 * WIDTH);
				int py = (int)((trajectory_y[j] + 2.0) / 4.0 * HEIGHT);
				if (px >= 0 && px < WIDTH && py >= 0 && py < HEIGHT) {
					int idx = py * WIDTH + px;
					if (channel == 0) accumR[idx]++;
					else if (channel == 1) accumG[idx]++;
					else accumB[idx]++;
				}
			}
		}
    }

    int maxR = 0, maxG = 0, maxB = 0;
	for (int i = 0; i < WIDTH * HEIGHT; i++) {
		if (accumR[i] > maxR) maxR = accumR[i];
		if (accumG[i] > maxG) maxG = accumG[i];
		if (accumB[i] > maxB) maxB = accumB[i];
	}

	for (int y = 0; y < HEIGHT; y++) {
		for (int x = 0; x < WIDTH; x++) {
			int idx = y * WIDTH + x;
			int r = (int)(255.0 * sqrt((double)accumR[idx] / maxR));
			int g = (int)(255.0 * sqrt((double)accumG[idx] / maxG));
			int b = (int)(255.0 * sqrt((double)accumB[idx] / maxB));

			int color = (r << 16) | (g << 8) | b;
			my_mlx_pixel_put(vars->img, x, y, color);
		}
	}
	rotate_image_90_clockwise(vars);
}


void	buddhabrot(t_vars *vars)
{
    static int *accum = NULL;
    if (!accum)
        accum = calloc(WIDTH * HEIGHT, sizeof(int)); // tableau pour accumulation

    for (int s = 0; s < SAMPLES; s++) {
        double cr = ((double)rand() / RAND_MAX) * 4.0 - 2.0; // [-2, 2]
        double ci = ((double)rand() / RAND_MAX) * 4.0 - 2.0; // [-2, 2]

        double zr = 0.0, zi = 0.0;
        double trajectory_x[MAX_ITER];
        double trajectory_y[MAX_ITER];

        int iter = 0;
        int escaped = 0;

        // Première passe : calcul et stockage de la trajectoire
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

        // Si diverge, on incrémente dans la matrice accumulation
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

    // Normalisation et affichage final
    int max_val = 0;
    for (int i = 0; i < WIDTH * HEIGHT; i++)
        if (accum[i] > max_val)
            max_val = accum[i];

    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            int val = accum[y * WIDTH + x];
            int color = (val * 255) / max_val;
            if (color <= 256)
                color += 25;
            my_mlx_pixel_put(vars->img, x, y, (color << 8) | color);
        }
    }
}

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

            int color = (r << 16) | (g << 8) | b;
            my_mlx_pixel_put(vars->img, x, y, color);
        }
    }

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

    // lancer les threads
    for (int t = 0; t < THREADS; t++) {
        data[t].vars = vars;
        data[t].accum_local = calloc(WIDTH * HEIGHT, sizeof(int));
        data[t].samples = SAMPLES / THREADS;
        data[t].seed = rand();
        pthread_create(&threads[t], NULL, buddhabrot_worker, &data[t]);
    }

    // attendre les threads et fusionner
    for (int t = 0; t < THREADS; t++) {
        pthread_join(threads[t], NULL);

        for (int i = 0; i < WIDTH * HEIGHT; i++) {
            accum_global[i] += data[t].accum_local[i];
        }
        free(data[t].accum_local);
    }

    // normalisation
    int max_val = 0;
    for (int i = 0; i < WIDTH * HEIGHT; i++)
        if (accum_global[i] > max_val)
            max_val = accum_global[i];

    // rendu
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            int val = accum_global[y * WIDTH + x];
            int color = (val * 255) / max_val;
            // if (color <= 256)
            //     color += 25;
            my_mlx_pixel_put(vars->img, x, y, (color << 16) | (color << 8) | color);
        }
    }

    rotate_image_90_clockwise(vars);
}

void *buddhabrot_colored_p_worker(void *arg)
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

void	buddhabrot_colored_p_thread(t_vars *vars)
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
        data[t].accumR = calloc(WIDTH * HEIGHT, sizeof(int));
        data[t].accumG = calloc(WIDTH * HEIGHT, sizeof(int));
        data[t].accumB = calloc(WIDTH * HEIGHT, sizeof(int));
        data[t].samples = SAMPLES / THREADS;
        data[t].seed = rand();
        pthread_create(&threads[t], NULL, buddhabrot_colored_p_worker, &data[t]);
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

    rotate_image_90_clockwise(vars);
}
