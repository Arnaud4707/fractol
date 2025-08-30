/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amugisha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 14:45:54 by amugisha          #+#    #+#             */
/*   Updated: 2025/01/07 22:33:26 by amugisha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx/mlx.h"
#include "include/header.h"

double	get_audio_amp()
{
    static double t = 0;
    t += 0.1;
    return (sin(t) + 1.0) / 2.0;
}

void	analyse_audio(t_vars* vars)
{
	static int p = 0;

	if (vars->index_audio != p)
	{
		p = vars->index_audio;
		vars->audio_amp = get_audio_amp();
	}
}

void	audio_play(t_vars* vars)
{
	pid_t	pid;
	int		status;
    char cmd[256];

	status = 0;
	pid = fork();
	if (pid < 0)
	{
		write(2, "Error: fork\n", ft_strlen("Error: fork\n"));
		exit(1);
	}
	else if (pid == 0)
	{
		while (1)
        {
            if (!vars->playlist[vars->index_audio])
                vars->index_audio = 0;
            snprintf(cmd, sizeof(cmd), "paplay '%s'", vars->playlist[vars->index_audio]);
            system(cmd);
            vars->index_audio += 1;
        }
        exit(0);
	}
	else
		vars->audio_pid = pid;
}

void	audio_stop(t_vars *vars)
{
	char cmd[265];

    if (vars->audio_pid > 0)
    {
        kill(vars->audio_pid, SIGKILL);
        snprintf(cmd, sizeof(cmd), "pkill -f 'paplay %s'", vars->playlist[vars->index_audio]);
		system(cmd);
        vars->audio_pid = 0;
    }
}
