/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mm-furi <mm-furi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 16:52:34 by mm-furi           #+#    #+#             */
/*   Updated: 2024/11/13 17:04:02 by mm-furi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_map(t_data *data)
{
	int	y;

	y = 0;
	while (y < data->map_height)
	{
		free(data->map[y]);
		y++;
	}
	free(data->map);
}

void	free_player_frames(t_data *data)
{
	int	dir;
	int	frame;

	dir = 0;
	while (dir < 4)
	{
		frame = 0;
		while (frame < 3)
		{
			if (data->player.frames[dir][frame])
				mlx_destroy_image(data->mlx_ptr,
					data->player.frames[dir][frame]);
			frame++;
		}
		dir++;
	}
}

void	free_enemies(t_data *data)
{
	t_enemy	*current;
	t_enemy	*temp;

	current = data->enemies;
	while (current)
	{
		temp = current->next;
		free_enemy(data, current);
		current = temp;
	}
	data->enemies = NULL;
	data->enemy_count = 0;
}

void	free_enemy_frames(t_data *data, t_enemy *enemy)
{
	int	dir;
	int	frame;

	dir = 0;
	while (dir < 4)
	{
		frame = 0;
		while (frame < 3)
		{
			if (enemy->frames[dir][frame])
			{
				mlx_destroy_image(data->mlx_ptr, enemy->frames[dir][frame]);
				enemy->frames[dir][frame] = NULL;
			}
			frame++;
		}
		dir++;
	}
}

void	free_enemy(t_data *data, t_enemy *enemy)
{
	free_enemy_frames(data, enemy);
	free(enemy);
}
