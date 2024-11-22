/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mm-furi <mm-furi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 17:15:49 by mm-furi           #+#    #+#             */
/*   Updated: 2024/11/19 14:39:21 by mm-furi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	initialize_enemies(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < data->map_height)
	{
		x = 0;
		while (data->map[y][x])
		{
			if (data->map[y][x] == 'M')
			{
				add_enemy(data, x, y);
				data->map[y][x] = '0';
			}
			x++;
		}
		y++;
	}
}

int	initialize_data(t_data *data)
{
	ft_memset(data, 0, sizeof(t_data));
	data->move_count = 0;
	data->game_state = PLAYING;
	data->blink_counter = 0;
	return (0);
}

int	initialize_game(t_data *data)
{
	if (initialize_enemies_and_player(data) == -1)
		return (-1);
	if (initialize_window_and_image(data) == -1)
		return (-1);
	return (0);
}

int	initialize_enemies_and_player(t_data *data)
{
	t_enemy	*current_enemy;

	init_enemies(data);
	current_enemy = data->enemies;
	while (current_enemy)
	{
		current_enemy->current_frame = 0;
		current_enemy = current_enemy->next;
	}
	data->player.current_direction = 0;
	data->player.current_frame = 0;
	data->piece.current_frame = 0;
	if (find_player_position(data) == -1)
		return (-1);
	return (0);
}

int	initialize_window_and_image(t_data *data)
{
	if (!data->win_ptr)
		return (-1);
	data->img = mlx_new_image(data->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!data->img)
		return (-1);
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel,
			&data->line_length, &data->endian);
	if (!data->addr)
		return (-1);
	return (0);
}
