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

# define HEIGHT 800
# define SAMPLES 500000
# define WIDTH 800
# define MAX_ITER 1000

# include <stddef.h>
# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include <string.h>
# include <unistd.h>

#define THREADS 20   // nombre de threads, adapte à ton CPU

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
	int		f;
	int		color;
	int		play;
	int		*palette;
	int		zoom_i;
	double zoomm;
	double offsetX;
	double offsetY;
	double hue_shift;
}				t_vars;

typedef struct {
    t_vars *vars;
    int *accum_local;
    int samples;
    unsigned int seed;
} ThreadData;

typedef struct {
    t_vars *vars;
    int *accumR;
    int *accumG;
    int *accumB;
    int samples;
    unsigned int seed;
} ThreadDataColor;

int		closey(t_vars *vars);
int		loop_hook(void *arg);
int		zoom(int button, int x, int y, t_vars *vars);
int		key(int keycode, t_vars *vars);
void	buddhabrot(t_vars *vars);
void	buddhabrot_thread(t_vars *vars);
void	buddhabrot_colored(t_vars *vars);
void	buddhabrot_colored_thread(t_vars *vars);
void	buddhabrot_colored_thread_animation(t_vars *vars);
void	buddhabrot_colored_p(t_vars *vars);
void	buddhabrot_colored_p_thread(t_vars *vars);
void	calcule_dragon(t_vars *vars);
void	calcule_b(t_vars *vars, int x, int y);
void	calcule_m(t_vars *vars, int x, int y);
void	calcule_m4(t_vars *vars, int x, int y);
void	calcule_m6(t_vars *vars, int x, int y);
void	calcule_j(t_vars *vars, int x, int y);
void	zoom_dragon(t_vars* vars, double i);
void	fractal(t_vars *vars, void (*calcule)(t_vars *, int, int));
int		check_arg(int arg, char **argv, t_vars *vars);
int		check_arg_julia(char *src, int c, t_vars *vars);
void	errors(int error, t_vars *vars);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
int		vars_set_dragon(t_vars *vars);
int		vars_set_mandelbrot4(t_vars *vars);
int		vars_set_burning_ship(t_vars *vars);
int		vars_set_mandelbrot(t_vars *vars);
int		vars_set_Buddhabrot(t_vars *vars);
int		vars_set_BuddhabrotA(t_vars *vars);
int		vars_set_Buddhabrot3(t_vars *vars);
int		vars_set_Buddhabrot2(t_vars *vars);
int		vars_set_mandelbrot6(t_vars *vars);
void	rotate_image_90_clockwise(t_vars *vars);
int		vars_set_julia(t_vars *vars);
void	function_asymptote(int button, double x, double y, t_vars *vars);
void	horizontal(int keycode, t_vars *vars);
void	vertical(int keycode, t_vars *vars);
int		vars_set_julia_move(t_vars *vars);
void	set_color(int keycode, t_vars *vars);
void	function_asymptote_click(int button, double x, double y, t_vars *vars);
void	action_zoom(int button, double tmpx, double tmpy, t_vars *vars);
int		len(char *str);
int		julia_move(int x, int y, t_vars *vars);
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
int		len(char *str);
int		ckeck(char *s, int l);
double	gamma_correct(double value);

#endif
