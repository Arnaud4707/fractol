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
            my_mlx_pixel_put(vars->img, x, y, ((color) << 16)|((color) << 8) | color);
        }
    }
	rotate_image_90_clockwise(vars);
}