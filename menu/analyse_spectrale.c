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

void	analyse_audio(t_vars *vars)
{
	int read = sf_read_short(vars->snd, vars->audio_buf, vars->buffer_size * vars->sfinfo.channels);
	if (read <= 0)
	{
		sf_seek(vars->snd, 0, SEEK_SET);
		read = sf_read_short(vars->snd, vars->audio_buf, vars->buffer_size * vars->sfinfo.channels);
	}

	for (int i = 0; i < vars->buffer_size; i++)
		vars->fft_in[i] = (double)vars->audio_buf[i * vars->sfinfo.channels] / 32768.0;

	fftw_execute(vars->fft_plan);

	double bass = 0, mid = 0, treble = 0;
	for (int i = 0; i < vars->buffer_size / 2 + 1; i++)
	{
		double mag = sqrt(vars->fft_out[i][0] * vars->fft_out[i][0] + vars->fft_out[i][1] * vars->fft_out[i][1]);
		double freq = (double)i * vars->sfinfo.samplerate / vars->buffer_size;

		if (freq < 200)
			bass += mag;
		else if (freq < 2000)
			mid += mag;
		else
			treble += mag;
	}

	double norm = (bass + mid + treble) + 1e-9;
	bass /= norm;
	mid /= norm;
	treble /= norm;

	vars->bass = 0.8 * vars->bass + 0.2 * bass;
	vars->mid = 0.8 * vars->mid + 0.2 * mid;
	vars->treble = 0.8 * vars->treble + 0.2 * treble;

	vars->audio_amp = vars->bass;
}

void	init_analyse_audio(t_vars* vars)
{
	vars->snd = sf_open(vars->playlist[vars->index_audio], SFM_READ, &vars->sfinfo);
    if (!vars->snd) {
        perror("sf_open");
        exit(0);
    }

    vars->audio_buf = malloc(vars->buffer_size * vars->sfinfo.channels * sizeof(short));
    vars->fft_in = fftw_malloc(sizeof(double) * vars->buffer_size);
    vars->fft_out = fftw_malloc(sizeof(fftw_complex) * (vars->buffer_size/(1 + 1) + 1));
    vars->fft_plan = fftw_plan_dft_r2c_1d(vars->buffer_size, vars->fft_in, vars->fft_out, FFTW_ESTIMATE);
}