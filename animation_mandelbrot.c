/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation_mandelbrot.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amugisha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 16:35:22 by amugisha          #+#    #+#             */
/*   Updated: 2025/01/06 21:27:25 by amugisha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx/mlx.h"
#include "header.h"

// void *fractal_power_worker(void *arg)
// {
//     ThreadDataMandelbrot *data = (ThreadDataMandelbrot *)arg;
//     t_vars *vars = data->vars;
//     t_data* img = vars->img_animation_mandelbrot[1 - vars->current];

//     for (int y = data->y_start; y < data->y_end; y++)
//     {
//         for (int x = 0; x < WIDTH_ANIMATION; x++)
//         {
//             int i = 0;
//             vars->zr = 0;
//             vars->zi = 0;
//             double cr = x / vars->ix + vars->xmin;
//             double ci = y / vars->iy + vars->ymin;

//             while ((vars->zr * vars->zr + vars->zi * vars->zi) < 4.0 && i < vars->max_iteration)
//             {
//                 double r = sqrt(vars->zr * vars->zr + vars->zi * vars->zi);
//                 double theta = atan2(vars->zi, vars->zr);

//                 double r_power = pow(r, data->power);
//                 double theta_power = theta * data->power;

//                 vars->zr = r_power * cos(theta_power) + cr;
//                 vars->zi = r_power * sin(theta_power) + ci;
//                 i++;
//             }

//             if (i >= vars->max_iteration)
//                 my_mlx_pixel_put(img, x, y, 0x000000);
//             else
//                 my_mlx_pixel_put(img, x, y, vars->palette[i]);
//         }
//     }
//     return NULL;
// }

// void fractal_power_threaded(t_vars *vars, double power)
// {
//     pthread_t threads[THREADS];
//     ThreadDataMandelbrot data[THREADS];
//     int slice = HEIGHT_ANIMATION / THREADS;

//     vars->ix = WIDTH_ANIMATION / (vars->xmax - vars->xmin);
//     vars->iy = HEIGHT_ANIMATION / (vars->ymax - vars->ymin);

//     for (int t = 0; t < THREADS; t++)
//     {
//         data[t].vars = vars;
//         data[t].power = power;
//         data[t].y_start = t * slice;
//         data[t].y_end = (t == THREADS - 1) ? HEIGHT_ANIMATION : (t + 1) * slice;

//         pthread_create(&threads[t], NULL, fractal_power_worker, &data[t]);
//     }

//     for (int t = 0; t < THREADS; t++)
//         pthread_join(threads[t], NULL);
// }

void calcule_m_power(t_vars *vars, int x, int y, double power)
{
    int     i;

    i = 0;
    vars->cr = x / vars->ix + vars->xmin;
    vars->ci = y / vars->iy + vars->ymin;
    vars->zr = 0;
    vars->zi = 0;

    while ((vars->zr * vars->zr + vars->zi * vars->zi) < 4.0 && i < vars->max_iteration)
    {
        double r = sqrt(vars->zr * vars->zr + vars->zi * vars->zi);
        double theta = atan2(vars->zi, vars->zr);
        double r_power = pow(r, power);
        double theta_power = theta * power;
        vars->zr = r_power * cos(theta_power) + vars->cr;
        vars->zi = r_power * sin(theta_power) + vars->ci;
        i++;
    }

    if (i >= vars->max_iteration)
        my_mlx_pixel_put(vars->img, x, y, 0x000000);
    else
        my_mlx_pixel_put(vars->img, x, y, vars->palette[i]);
}

void fractal_power(t_vars *vars, double power)
{
    int x, y;

    vars->ix = WIDTH_ANIMATION / (vars->xmax - vars->xmin);
    vars->iy = HEIGHT_ANIMATION / (vars->ymax - vars->ymin);

    for (y = 0; y < HEIGHT_ANIMATION; y++)
    {
        for (x = 0; x < WIDTH_ANIMATION; x++)
        {
            calcule_m_power(vars, x, y, power);
        }
    }
}

int loop_hook_mandelbrot_pussance_n(t_vars *vars)
{
    static double power = 2.0;
    static int direction = 1;

    power += 0.01 * direction;

    if (power >= 7.0)
        direction = -1;
    else if (power <= 2.0)
        direction = 1;

    fractal_power(vars, power);
    mlx_put_image_to_window(vars->mlx, vars->win, vars->img->img, 0, 0);
    return (0);
}

// int	loop_hook_zoom_mandelbrot(t_vars* vars)
// {
// 	action_zoom(4, -0.743517833, -0.127094578, vars);
// 	fractal(vars, calcule_m);
// 	mlx_put_image_to_window(vars->mlx, vars->win, vars->img->img, 0, 0);
// 	usleep(33000);
// 	return (0);
// }
// int loop_hook_mandelbrot_pussance_n_thread(t_vars *vars)
// {
//     static double power = 2.0;
//     static int direction = 1;

//     power += 0.01 * direction;

//     if (power >= 7.0)
//         direction = -1;
//     else if (power <= 2.0)
//         direction = 1;

//     fractal_power_threaded(vars, power);
//     vars->current = 1 - vars->current;
//     mlx_put_image_to_window(vars->mlx, vars->win, vars->img_animation_mandelbrot[vars->current]->img, 0, 0);
//     return (0);
// }
