/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verification.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amugisha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 16:44:08 by amugisha          #+#    #+#             */
/*   Updated: 2025/01/11 01:12:36 by amugisha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx/mlx.h"
#include "../../include/header.h"

void	pass(int *i, int *signe, char *str)
{
	if (str[*i] == 43 || str[*i] == 45)
	{
		if (str[*i] == 45)
			*signe = -1;
		*i = *i + 1;
	}
	while (str[*i + 1] && str[*i] == 48 && str[*i + 1] == 48)
		*i = *i + 1;
}

void	restor(int *count, double *result)
{
	while (*count > 0)
	{
		*result = *result / 10;
		*count = *count - 1;
	}
}

int	check_int(char *str, double *result)
{
	int	i;
	int	signe;
	int	count;

	i = 0;
	signe = 1;
	*result = 0;
	count = 0;
	if (len(str) > 308)
		return (-1);
	pass(&i, &signe, str);
	while (str[i])
	{
		if (str[i] >= 48 && str[i] <= 57 && count != 1)
			*result = *result * 10 + str[i] - 48;
		else if (count == 1 && str[i] == 46)
			;
		else
			return (-1);
		i++;
		count++;
	}
	restor(&count, result);
	*result = *result * signe * 100;
	return (0);
}

int	check_arg_julia(char *src, int c, t_vars *vars)
{
	double	result;

	if (check_int(src, &result) == -1)
		return (-1);
	if (c == 2 && (result >= -1.5 && result <= 1.5))
		vars->cr = result;
	else if (c == 3 && (result >= -1.5 && result <= 1.5))
		vars->ci = result;
	else
		return (-1);
	return (0);
}

int	check_arg(int arg, char **argv, t_vars *vars)
{
	int	error;

	if (arg < 2)
		return (-1);
	if (ft_strncmp(argv[1], "Buddhabrot", 10) != 0
			|| ckeck(argv[1], 7) == -1)
	{
		if (ft_strncmp(argv[1], "MandelbrotA", 11) != 0
			|| ckeck(argv[1], 10) == -1 || arg < 4)
		{
			if (ft_strncmp(argv[1], "Buddhabrot2", 11) != 0
				|| ckeck(argv[1], 9) == -1)
			{
				if (ft_strncmp(argv[1], "BuddhabrotA", 11) != 0
					|| ckeck(argv[1], 11) == -1)
				{
					if (ft_strncmp(argv[1], "SpongMenger", 11) != 0
						|| ckeck(argv[1], 12) == -1 || arg < 3)
					{
						if (ft_strncmp(argv[1], "Dragon", 6) != 0
							|| ckeck(argv[1], 5) == -1)
						{
							if (ft_strncmp(argv[1], "BurningShip", 11) != 0
								|| ckeck(argv[1], 4) == -1)
							{
								if (ft_strncmp(argv[1], "Mandelbrot", 10) != 0
									|| ckeck(argv[1], 1) == -1)
								{
									if (ft_strncmp(argv[1], "Mandelbrot_zoom", 15) != 0
										|| ckeck(argv[1], 8) == -1)
									{
										if (ft_strncmp(argv[1], "BuddhabrotA2", 12) != 0
										|| ckeck(argv[1], 6) == -1)
										{
											if (ft_strncmp(argv[1], "JuliaMove", 9) != 0 || ckeck(argv[1], 3) == -1)
											{
												if (ft_strncmp(argv[1], "Julia", 5) != 0 || arg < 4
													|| ckeck(argv[1], 2) == -1)
													return (-1);
												else if (check_arg_julia(argv[2], 2, vars) != 0
													|| check_arg_julia(argv[3], 3, vars) != 0)
													return (-1);
												else
													error = vars_set_julia(vars);
											}
											else
												error = vars_set_julia_move(vars);
										}
										else
											error = vars_set_buddhabrot_animation_2(vars);
									}
									else
										error = vars_set_mandelbrot_zoom(vars);
								}
								else
									error = vars_set_mandelbrot(vars);
							}
							else
								error = vars_set_burning_ship(vars);
						}
						else
							error = vars_set_dragon(vars);
					}
					else
						error = vars_set_spondMenger(vars, argv[2]);
				}
				else
					error = vars_set_BuddhabrotA(vars);
			}
			else
				error = vars_set_Buddhabrot2(vars);
		}
		else
			error = vars_set_MandelbrotA(vars, argv[2], argv[3]);
	}
	else
		error = vars_set_Buddhabrot(vars);
	return (error);
}
