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
    int read = sf_read_short(vars->snd, vars->audio_buf, vars->buffer_size * vars->sfinfo.channels);
    if (read <= 0) {
        sf_seek(vars->snd, 0, SEEK_SET);
        read = sf_read_short(vars->snd, vars->audio_buf, vars->buffer_size * vars->sfinfo.channels);
    }

    for (int i = 0; i < vars->buffer_size; i++)
        vars->fft_in[i] = (double)vars->audio_buf[i*vars->sfinfo.channels] / 32768.0;

    fftw_execute(vars->fft_plan);

    double bass = 0, mid = 0, treble = 0;
    for (int i = 0; i < vars->buffer_size/2+1; i++) {
        double mag = sqrt(vars->fft_out[i][0]*vars->fft_out[i][0] + vars->fft_out[i][1]*vars->fft_out[i][1]);
        double freq = (double)i * vars->sfinfo.samplerate / vars->buffer_size;

        if (freq < 200) bass += mag;
        else if (freq < 2000) mid += mag;
        else treble += mag;
    }

    double norm = (bass + mid + treble) + 1e-9;
    bass   /= norm;
    mid    /= norm;
    treble /= norm;

    vars->bass   = 0.8 * vars->bass   + 0.2 * bass;
    vars->mid    = 0.8 * vars->mid    + 0.2 * mid;
    vars->treble = 0.8 * vars->treble + 0.2 * treble;

	vars->audio_amp = vars->bass;
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
		setpgid(0, 0);
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
    if (vars->audio_pid > 0)
	{
        kill(-vars->audio_pid, SIGKILL);
        waitpid(vars->audio_pid, NULL, 0);
        vars->audio_pid = 0;
    }
}
