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

# include <stddef.h>

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
}				t_vars;
int		closey(t_vars *vars);
int		zoom(int button, int x, int y, t_vars *vars);
int		key(int keycode, t_vars *vars);
void	calcule_m(t_vars *vars, int x, int y);
void	calcule_j(t_vars *vars, int x, int y);
void	calcule_t(t_vars *vars, int x, int y);
void	fractal(t_vars *vars, void (*calcule)(t_vars *, int, int));
int		check_arg(int arg, char **argv, t_vars *vars);
int		check_arg_julia(char *src, int c, t_vars *vars);
void	errors(int error, t_vars *vars);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
int		vars_set_mandelbrot(t_vars *vars);
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
