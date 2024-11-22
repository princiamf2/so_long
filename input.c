/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mm-furi <mm-furi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 17:11:12 by mm-furi           #+#    #+#             */
/*   Updated: 2024/11/19 12:38:47 by mm-furi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	key_press(int keycode, t_data *data)
{
	int	new_x;
	int	new_y;
	int	map_x;
	int	map_y;

	if (data->game_state == GAME_OVER && keycode == KEY_SPACE)
	{
		reset_game(data);
		return (0);
	}
	new_x = data->player.x;
	new_y = data->player.y;
	handle_movement(keycode, data, &new_x, &new_y);
	map_x = (new_x + TILE_SIZE / 2) / TILE_SIZE;
	map_y = (new_y + TILE_SIZE / 2) / TILE_SIZE;
	if (map_x >= 0 && map_x < data->map_width && map_y >= 0
		&& map_y < data->map_height && data->map[map_y][map_x] != '1')
	{
		update_player_position(keycode, data, new_x, new_y);
	}
	check_tile(data, map_x, map_y);
	return (0);
}

int	is_movement_key(int keycode)
{
	return (keycode == KEY_W || keycode == KEY_HAUT || keycode == KEY_S
		|| keycode == KEY_BAS || keycode == KEY_A || keycode == KEY_GAUCHE
		|| keycode == KEY_D || keycode == KEY_DROITE);
}

void	process_movement(int keycode, t_data *data, int *new_x, int *new_y)
{
	if (keycode == KEY_W || keycode == KEY_HAUT)
	{
		data->player.current_direction = 3;
		*new_y -= MOVE_SPEED;
	}
	else if (keycode == KEY_S || keycode == KEY_BAS)
	{
		data->player.current_direction = 0;
		*new_y += MOVE_SPEED;
	}
	else if (keycode == KEY_A || keycode == KEY_GAUCHE)
	{
		data->player.current_direction = 1;
		*new_x -= MOVE_SPEED;
	}
	else if (keycode == KEY_D || keycode == KEY_DROITE)
	{
		data->player.current_direction = 2;
		*new_x += MOVE_SPEED;
	}
}

void	update_player_position(int keycode, t_data *data, int new_x, int new_y)
{
	int	map_x;
	int	map_y;

	map_x = (new_x + TILE_SIZE / 2) / TILE_SIZE;
	map_y = (new_y + TILE_SIZE / 2) / TILE_SIZE;
	data->player.x = new_x;
	data->player.y = new_y;
	if (is_movement_key(keycode))
		data->move_count++;
	if (data->map[map_y][map_x] == 'C')
	{
		data->map[map_y][map_x] = '0';
		data->collect_collecter++;
	}
	handle_enemy_collision(data);
}

void	check_tile(t_data *data, int map_x, int map_y)
{
	char	tile;

	tile = data->map[map_y][map_x];
	if (data->collect_collecter == data->total_collect)
	{
		if (tile == 'E')
		{
			write(1, "Félicitations ! Vous avez terminé le niveau.\n", 45);
			exit_game(data);
		}
	}
}
