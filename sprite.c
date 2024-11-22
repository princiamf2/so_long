/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mm-furi <mm-furi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 16:01:54 by mm-furi           #+#    #+#             */
/*   Updated: 2024/11/13 17:27:04 by mm-furi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	animate_player(t_data *data)
{
	static int	time = 0;

	if (data->cur_input > -1)
		data->cur_input -= 1;
	if (time++ >= ANIMATION_SPEED)
	{
		if (data->cur_input == -1)
			data->player.current_frame = 1;
		else
		{
			data->player.current_frame = (data->player.current_frame + 1) % 3;
			if (data->player.current_frame == 1)
				data->player.current_frame++;
		}
		time = 0;
	}
}

void	update_enemy_direction(t_enemy *enemy)
{
	if (rand() % 60 == 0)
		enemy->current_direction = rand() % 4;
}

void	calculate_new_position(t_enemy *enemy, int *new_x, int *new_y)
{
	*new_x = enemy->x;
	*new_y = enemy->y;
	if (enemy->current_direction == 3)
		*new_y -= MOVE_SPEED_ENEMY;
	else if (enemy->current_direction == 0)
		*new_y += MOVE_SPEED_ENEMY;
	else if (enemy->current_direction == 1)
		*new_x -= MOVE_SPEED_ENEMY;
	else if (enemy->current_direction == 2)
		*new_x += MOVE_SPEED_ENEMY;
}

int	is_move_valid(t_data *data, int new_x, int new_y)
{
	int	map_x;
	int	map_y;

	map_x = (new_x + TILE_SIZE / 2) / TILE_SIZE;
	map_y = (new_y + TILE_SIZE / 2) / TILE_SIZE;
	if (map_x >= 0 && map_x < data->map_width && map_y >= 0
		&& map_y < data->map_height && data->map[map_y][map_x] != '1')
		return (1);
	return (0);
}

void	animate_collect(t_data *data)
{
	static int	time = 0;

	if (time++ >= ANIMATION_SPEED)
	{
		data->piece.current_frame = (data->piece.current_frame + 1) % 6;
		time = 0;
	}
}
