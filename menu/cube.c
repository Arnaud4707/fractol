/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intro.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amugisha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 14:45:54 by amugisha          #+#    #+#             */
/*   Updated: 2025/01/07 22:33:26 by amugisha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx/mlx.h"
#include "include/header.h"

t_point3D	cube_vertices[8] = {
    {-1, -1, -1}, {1, -1, -1},
    {1,  1, -1}, {-1,  1, -1},
    {-1, -1,  1}, {1, -1,  1},
    {1,  1,  1}, {-1,  1,  1}
};

int edges[12][2] = {
    {0,1},{1,2},{2,3},{3,0},
    {4,5},{5,6},{6,7},{7,4},
    {0,4},{1,5},{2,6},{3,7}
};

// int loop_hook_cube2(t_vars *vars)
// {
//     static double ax = 0, ay = 0, az = 0;

//     draw_cube(vars, ax, ay, az);

//     ax += 0.02;
//     ay += 0.03;
//     az += 0.01;
//     return 0;
// }

int loop_hook_cube(t_vars *vars)
{
    static double ax = 0, ay = 0, az = 0;
    double speed_base = 0.0175;

    double speed_x = speed_base + vars->bass   * 0.02;
    double speed_y = speed_base + vars->mid    * 0.03;
    double speed_z = speed_base + vars->treble * 0.01;

    ax += speed_x;
    ay += speed_y;
    az += speed_z;

    draw_cube(vars, ax, ay, az);
    return 0;
}


t_point3D	rotate_point(t_point3D p, double ax, double ay, double az)
{
    double cy = cos(ax), sy = sin(ax);
    double ny = p.y * cy - p.z * sy;
    double nz = p.y * sy + p.z * cy;
    p.y = ny; p.z = nz;

    double cx = cos(ay), sx = sin(ay);
    double nx = p.x * cx + p.z * sx;
    nz = -p.x * sx + p.z * cx;
    p.x = nx; p.z = nz;

    double cz = cos(az), sz = sin(az);
    nx = p.x * cz - p.y * sz;
    ny = p.x * sz + p.y * cz;
    p.x = nx; p.y = ny;

    return p;
}

t_point2D	project_point(t_point3D p, int w, int h, double scale)
{
    t_point2D proj;
    double d = 3.0;
    double factor = scale / (p.z + d);
    proj.x = (int)(w / 2 + p.x * factor);
    proj.y = (int)(h / 2 + p.y * factor);
    return proj;
}


void	draw_line(t_vars *vars, int x0, int y0, int x1, int y1, int color)
{
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;
    int err = dx - dy;

    while (1)
    {
        my_mlx_pixel_put(vars->img, x0, y0, color);
        if (x0 == x1 && y0 == y1)
            break;
        int e2 = 2 * err;
        if (e2 > -dy) { err -= dy; x0 += sx; }
        if (e2 < dx)  { err += dx; y0 += sy; }
    }
}

void	draw_cube(t_vars *vars, double ax, double ay, double az)
{
    t_point2D proj[8];

    double scale = 0.75 + 0.75 * vars->bass;

    for (int i = 0; i < 8; i++)
    {
        t_point3D p = rotate_point(cube_vertices[i], ax, ay, az);

        p.x *= scale;
        p.y *= scale;
        p.z *= scale;
        proj[i] = project_point(p, vars->largeur, vars->hauteur, 300);
    }

    double hue   = fmod(vars->mid * 520.0, 360.0);
    double sat   = 0.4 + 0.35 * vars->treble;
	double light = 0.4 + 0.2 * vars->bass;

    t_rgb col = hsl_to_rgb2(hue, sat, light);
    int line_color = (col.r << 16) | (col.g << 8) | col.b;
    for (int i = 0; i < 12; i++)
    {
        int a = edges[i][0];
        int b = edges[i][1];
        draw_line(vars, proj[a].x, proj[a].y, proj[b].x, proj[b].y, (2147483647 - line_color));
    }
}
