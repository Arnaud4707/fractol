/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amugisha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 21:08:42 by amugisha          #+#    #+#             */
/*   Updated: 2025/01/10 17:38:48 by amugisha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# define LUT_SIZE 1000
# define HEIGHT 800
# define HEIGHT_ANIMATION 500
# define WIDTH 800
# define WIDTH_ANIMATION 500
# define SAMPLES 500000
# define MAX_ITER 1000

# include <stddef.h>
# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include <string.h>
# include <unistd.h>
#include "../libft/libft.h"

#define THREADS 20

int		ft_strncmp(const char *s1, const char *s2, size_t n);
typedef struct s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;
typedef struct s_vars {
	char	*name;
	void	*mlx;
	void	*win;
	t_data	*img;
    t_data  *img_animation_mandelbrot[2];
	int     current;
	double	max_iteration;
	double	largeur;
	double	hauteur;
	double	xmin;
	double	xmax;
	double	ymin;
	double	ymax;
	double	cr;
	double	ci;
	double	zr;
	double	zi;
	double	ix;
	double	iy;
	int		power_min;
	int		power_max;
	int		f;
	int		color;
	int		key;
	int		current_key;
	int		play;
	int		*palette;
	int		zoom_i;
	int		step;
	double 	zoomm;
	double	offsetX;
	double 	offsetY;
	double 	hue_shift;
	double sqrtLUT[LUT_SIZE];
}				t_vars;

typedef struct {
    t_vars 	*vars;
    int 	*accum_local;
    int 	samples;
    unsigned int seed;
} ThreadData;

typedef struct {
    t_vars 	*vars;
    int 	*accumR;
    int 	*accumG;
    int 	*accumB;
    int 	samples;
    unsigned int seed;
} ThreadDataColor;

typedef struct {
    t_vars 	*vars;
    double	power;
    int 	y_start;
    int 	y_end;
} ThreadDataMandelbrot;

typedef struct {
	double x;
	double y;
	double z;
} t_point3D;

typedef struct {
	int x;
	int y;
} t_point2D;

void	action_zoom(int button, double tmpx, double tmpy, t_vars *vars);
void	background(t_vars* vars);
int		closey(t_vars *vars);
void	cube(t_vars* vars);
void	buddhabrot(t_vars *vars);
void	buddhabrot_thread(t_vars *vars);
void	buddhabrot_colored(t_vars *vars);
void	buddhabrot_colored_thread(t_vars *vars);
void	buddhabrot_colored_thread_animation(t_vars *vars);
void	buddhabrot_colored_thread_animation_2(t_vars *vars);
void	buddhabrot_colored_p(t_vars *vars);
void	*buddhabrot_colored_worker_animation(void *arg);
void	button_start(t_vars* vars);
void	calcule_dragon(t_vars *vars);
void	calcule_b(t_vars *vars, int x, int y);
void	calcule_m(t_vars *vars, int x, int y);
void	calcule_j(t_vars *vars, int x, int y);
int		check_arg(int arg, char **argv, t_vars *vars);
int		check_arg_julia(char *src, int c, t_vars *vars);
int		ckeck(char *s, int l);
void	colord_Buddhabrot(t_vars* vars, int x, int y);
void	colord_Buddhabrot_r(t_vars* vars, int x, int y);
void	colord_Buddhabrot_g(t_vars* vars, int x, int y);
void	colord_Buddhabrot_b(t_vars* vars, int x, int y);
void	colord_Buddhabrot_y(t_vars* vars, int x, int y);
void	colord_Buddhabrot_c(t_vars* vars, int x, int y);
void	colord_Buddhabrot_p(t_vars* vars, int x, int y);
void	color_buddhabrot_colored_p(t_vars* vars, int *accumR_global, int *accumG_global, int *accumB_global);
void	drawMenger2D(t_vars *vars, int depth);
void	errors(int error, t_vars *vars);
int		event_button(int x, int y, t_vars *vars);
void	fractal(t_vars *vars, void (*calcule)(t_vars *, int, int));
void	function_asymptote(int button, double x, double y, t_vars *vars);
void	function_asymptote_click(int button, double x, double y, t_vars *vars);
double	gamma_correct(double value);
void	horizontal(int keycode, t_vars *vars);
void    hsv_to_rgb(double h, double s, double v, int *r, int *g, int *b);
void	init_sqrtLUT(t_vars* vars);
int		julia_move(int x, int y, t_vars *vars);
int		key(int keycode, t_vars *vars);
int		len(char *str);
void    letter_s(t_vars* vars);
int		loop_hook_buddhabrot_thread(void *arg);
int		loop_hook_buddhabrot_thread_2(void *arg);
int		loop_hook_display_menu(void* arg);
int 	loop_hook_mandelbrot_pussance_n(t_vars *vars);
int		loop_hook_zoom_mandelbrot(t_vars* vars);
void	menu(t_vars* vars);
int		move(int x, int y, t_vars *vars);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void	palette_color(int keycode, t_vars *vars);
int 	palette_fire(double t);
int 	palette_linear(double norm);
int		palette_test(double norm);
int 	palette_or(double norm);
int		precalculate_colors(t_vars *vars);
int		precalculate_colors_1(t_vars *vars);
int		precalculate_colors_2(t_vars *vars);
int		precalculate_colors_3(t_vars *vars);
int		precalculate_colors_r(t_vars *vars);
int		precalculate_colors_g(t_vars *vars);
int		precalculate_colors_b(t_vars *vars);
int		precalculate_colors_y(t_vars *vars);
int		precalculate_colors_4(t_vars *vars);
int		precalculate_colors_5(t_vars *vars);
void    precalculate_color_buddhabrot(t_vars* vars);
void	prepare_color_buddhabrot_thread(t_vars* vars, int *accumR_global, int *accumG_global, int *accumB_global);
void	prepare_color_buddhabrot(t_vars* vars, int x, int y, double norm);
void	rotate_image_90_clockwise(t_vars *vars);
void	set_color(int keycode, t_vars *vars);
int		vars_set_burning_ship(t_vars *vars);
int		vars_set_Buddhabrot(t_vars *vars);
int		vars_set_BuddhabrotA(t_vars *vars);
int		vars_set_Buddhabrot2(t_vars *vars);
int		vars_set_dragon(t_vars *vars);
int		vars_set_julia(t_vars *vars);
int		vars_set_julia_move(t_vars *vars);
int		vars_set_mandelbrot_zoom(t_vars *vars);
int		vars_set_mandelbrot(t_vars *vars);
int		vars_set_Menu(t_vars *vars);
int		vars_set_buddhabrot_animation_2(t_vars *vars);
int		vars_set_MandelbrotA(t_vars *vars, char *pmin, char* pmax);
int		vars_set_spondMenger(t_vars *vars, char *i);
void	vertical(int keycode, t_vars *vars);
int		zoom(int button, int x, int y, t_vars *vars);
void	zoom_dragon(t_vars* vars, double i);

#endif
