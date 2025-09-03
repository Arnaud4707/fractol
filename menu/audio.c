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

void	audio_play(t_vars *vars)
{
	pid_t pid;
	int status;
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

void 	vire_point(char* s)
{

}

void	draw_next_back_audio(t_vars *vars)
{
	char *audio;
	mlx_string_put(vars->mlx, vars->win, 82, 82, 0x000000, "Back");
	mlx_string_put(vars->mlx, vars->win, 80, 80, vars->selectAB, "Back");
	mlx_string_put(vars->mlx, vars->win, 132, 82, 0x000000, "Next");
	mlx_string_put(vars->mlx, vars->win, 130, 80, vars->selectAP, "Next");
	audio = ft_strchr(vars->playlist[vars->index_audio], '/');
	audio++;
	ft_
	mlx_string_put(vars->mlx, vars->win, 102, 57, 0x000000, audio);
	mlx_string_put(vars->mlx, vars->win, 100, 55, vars->selectAP, audio);
}

void switch_track(t_vars *vars, int new_index)
{
    audio_stop(vars);

    if (vars->snd)
    {
        sf_close(vars->snd);
        vars->snd = NULL;
    }

    int count = 0;
    while (vars->playlist[count])
        count++;
    if (count == 0) return;

    if (new_index < 0)
        new_index = count - 1;
    else if (new_index >= count)
        new_index = 0;

    vars->index_audio = new_index;

    audio_play(vars);
	if (vars->fft_plan)
		fftw_destroy_plan(vars->fft_plan);
	if (vars->fft_in)
		fftw_free(vars->fft_in);
	if (vars->fft_out)
		fftw_free(vars->fft_out);
	// fftw_cleanup();
    init_analyse_audio(vars);
}

void	audio_next(t_vars *vars)
{
    switch_track(vars, vars->index_audio + 1);
}

void	audio_back(t_vars *vars)
{
    switch_track(vars, vars->index_audio - 1);
}
