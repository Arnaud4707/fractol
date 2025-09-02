/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amugisha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 16:26:27 by amugisha          #+#    #+#             */
/*   Updated: 2025/01/07 19:58:27 by amugisha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx/mlx.h"
#include "../../include/header.h"

int	closey(t_vars *vars)
{
	if (vars->img && vars->img->img)
		mlx_destroy_image(vars->mlx, vars->img->img);
	if (vars->win)
		mlx_destroy_window(vars->mlx, vars->win);
	mlx_destroy_display(vars->mlx);
	free(vars->mlx);
	free(vars->img);
	free(vars->palette);
	audio_stop(vars);
	exit(0);
	return (0);
}

void	display_fractal(t_vars* vars, double tmpx, double tmpy, t_point3D* p)
{
	if (vars->f == -1 && p->z == 1 && (p->x >= 280 && p->x <= 520) && (p->y >= 370 && p->y <= 430))
		vars_set_Menu(vars);
	else if (vars->f == -2 && p->z == 1 && (p->y >= vars->hauteur - 80 && p->y <= vars->hauteur - 50)
		&& (p->x >= vars->largeur - 80 && p->x <= vars->largeur - 35))
		vars_set_Intro(vars);
	else if (vars->f != -1 && p->z == 1 && (p->y >= vars->hauteur - 80 && p->y <= vars->hauteur - 50)
		&& (p->x >= vars->largeur - 80 && p->x <= vars->largeur - 35))
	{
		if (vars->palette)
			free(vars->palette);
		ft_memset(vars->img->addr, 0, vars->hauteur * vars->img->line_length);
		vars_set_Menu(vars);
	}
	else if (vars->f == -2 && p->z == 1 && (p->y >= 90 && p->y <= 102))
		vars_set_mandelbrot(vars);
	else if (vars->f == -2 && p->z == 1 && (p->y >= 140 && p->y <= 152))
	{
		ft_memset(vars->img->addr, 0, vars->hauteur * vars->img->line_length);
		vars_set_julia_move(vars);
	}
	else if (vars->f == -2 && p->z == 1 && (p->y >= 190 && p->y <= 202))
		vars_set_burning_ship(vars);
	else if (vars->f == -2 && p->z == 1 && (p->y >= 240 && p->y <= 252))
		vars_set_spondMenger(vars, "1");
	else if (vars->f == -2 && p->z == 1 && (p->y >= 290 && p->y <= 302))
		vars_set_dragon(vars);
	else if (vars->f == -2 && p->z == 1 && (p->y >= 340 && p->y <= 352))
		vars_set_Buddhabrot(vars);
	else if (vars->f == -2 && p->z == 1 && (p->y >= 390 && p->y <= 402))
		vars_set_Buddhabrot2(vars);
	else if (vars->f == -2 && p->z == 1 && (p->y >= 440 && p->y <= 452))
	{
		ft_memset(vars->img->addr, 0, vars->hauteur * vars->img->line_length);
		vars_set_MandelbrotA(vars, "2", "5");
	}
	else if (vars->f == -2 && p->z == 1 && (p->y >= 490 && p->y <= 502))
		vars_set_BuddhabrotA(vars);
	else if (vars->f == -2 && p->z == 1 && (p->y >= 540 && p->y <= 552))
	{
		ft_memset(vars->img->addr, 0, vars->hauteur * vars->img->line_length);
		vars_set_mandelbrot_zoom(vars);
	}
	else if (vars->f == 5 && p->z == 4)
		zoom_dragon(vars, 0.8);
	else if (vars->f == 5 && p->z == 5)
		zoom_dragon(vars, 1.2);
	else if (vars->f != -2 && vars->f != -1 && vars->f != 9 
		&& vars-> f != 8 && vars->f != 7 && vars->f != 10 
		&& vars->f != 11 && vars->f != 6 && vars->f != 5
		&& (p->y < vars->hauteur - 80 || p->y > vars->hauteur - 50)
		&& (p->x < vars->largeur - 80 || p->x > vars->largeur - 35)
		&& (p->y < vars->hauteur && p->x < vars->largeur))
	{
		tmpx = (vars->xmax - vars->xmin) * ((double)(p->x) / vars->largeur);
		tmpy = (vars->ymax - vars->ymin) * ((double)(p->y) / vars->hauteur);
		action_zoom(p->z, tmpx, tmpy, vars);
		vars->need_drow = 1;
	}
}

int	zoom(int button, int x, int y, t_vars *vars)
{
	double	tmpx;
	double	tmpy;
	t_point3D p;

	tmpx = 0.0;
	tmpy = 0.0;
	p.x = x;
	p.y = y;
	p.z = button;
	click_next_back_audio(vars, &p);
	display_fractal(vars, tmpx, tmpy, &p);
	return (0);
}

void	zoom_dragon(t_vars* vars, double i)
{
	double cx = (vars->xmin + vars->xmax) / 2.0;
    double cy = (vars->ymin + vars->ymax) / 2.0;
    double half_width = (vars->xmax - vars->xmin) * i / 2.0;
    double half_height = (vars->ymax - vars->ymin) * i / 2.0;

	vars->xmin = cx - half_width;
	vars->xmax = cx + half_width;
	vars->ymin = cy - half_height;
	vars->ymax = cy + half_height;
	if (vars->ymin > 700.0 || vars->xmin < 70.0)
	{
		vars->xmin = 200;
		vars->xmax = 400;
		vars->ymin = 600;
		vars->ymax = 400;
	}
	vars->need_drow = 1;
}

int	arrow(int keycode, t_vars *vars)
{
	if (keycode == 65361)
		horizontal(keycode, vars);
	else if (keycode == 65363)
		horizontal(keycode, vars);
	else if (keycode == 65362)
		vertical(keycode, vars);
	else if (keycode == 65364)
		vertical(keycode, vars);
	return (0);
}

int	move(int x, int y, t_vars *vars)
{
	julia_move(x, y, vars);
	event_button(x, y, vars);
	return(0);
}

int	julia_move(int x, int y, t_vars *vars)
{
	if (vars->play == 1 && vars->f == 3)
	{
		vars->cr = x / vars->ix + vars->xmin;
		vars->ci = y / vars->iy + vars->ymin;
		vars->need_drow = 1;
	}
	return (0);
}

void	selectt(int y, t_vars* vars)
{
	if (vars->f == -2 && (y >= 90 && y <= 102))
		vars->selectM = 0x0000FF00;
	else if (vars->f == -2)
		vars->selectM = 0x00FFFFFF;
	if (vars->f == -2 && (y >= 140 && y <= 152))
		vars->selectJM = 0x0000FF00;
	else if (vars->f == -2)
		vars->selectJM = 0x00FFFFFF;
	if (vars->f == -2 && (y >= 190 && y <= 202))
		vars->selectB = 0x0000FF00;
	else if (vars->f == -2)
		vars->selectB = 0x00FFFFFF;
	if (vars->f == -2 && (y >= 240 && y <= 252))
		vars->selectS = 0x0000FF00;
	else if (vars->f == -2)
		vars->selectS = 0x00FFFFFF;
	if (vars->f == -2 && (y >= 290 && y <= 302))
		vars->selectD = 0x0000FF00;
	else if (vars->f == -2)
		vars->selectD = 0x00FFFFFF;
	if (vars->f == -2 && (y >= 340 && y <= 352))
		vars->selectBD = 0x0000FF00;
	else if (vars->f == -2)
		vars->selectBD = 0x00FFFFFF;
	if (vars->f == -2 && (y >= 390 && y <= 402))
		vars->selectBDC = 0x0000FF00;
	else if (vars->f == -2)
		vars->selectBDC = 0x00FFFFFF;
	if (vars->f == -2 && (y >= 440 && y <= 452))
		vars->selectMP = 0x0000FF00;
	else if (vars->f == -2)
		vars->selectMP = 0x00FFFFFF;
	if (vars->f == -2 && (y >= 490 && y <= 502))
		vars->selectBA = 0x0000FF00;
	else if (vars->f == -2)
		vars->selectBA = 0x00FFFFFF;
	if (vars->f == -2 && (y >= 540 && y <= 552))
		vars->selectMZ = 0x0000FF00;
	else if (vars->f == -2)
		vars->selectMZ = 0x00FFFFFF;
}

int	event_button(int x, int y, t_vars *vars)
{
	if (vars->f == -1 && x > 279 && x < 521 && y > 369 && y < 431)
		vars->color_start = 0x00FF0000;
	else if (vars->f == -1)
		vars->color_start = 0xFFFFFFFF;
	button_next_back_audio(x, y, vars);
	if (vars->f != -1 && (y >= vars->hauteur - 80 && y <= vars->hauteur - 50)
		&& (x >= vars->largeur - 80 && x <= vars->largeur - 35))
	{
		if ((unsigned int)vars->color_back == 0xFFFFFFFF)
		{
			vars->color_back = 0x00FF00FF;
			vars->need_drow = 1;
		}
	}
	else if (vars->f != -1 && (unsigned int)vars->color_back != 0xFFFFFFFF)
	{
		vars->color_back = 0xFFFFFFFF;
		vars->need_drow = 1;
	}
	selectt(y, vars);
	return (0);
}
