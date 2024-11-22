/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mm-furi <mm-furi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 16:48:35 by mm-furi           #+#    #+#             */
/*   Updated: 2024/11/15 16:11:05 by mm-furi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	handle_enemy_collision(t_data *data)
{
	t_enemy	*current;

	current = data->enemies;
	while (current)
	{
		if (data->player.x < current->x + TILE_SIZE && data->player.x
			+ TILE_SIZE > current->x && data->player.y < current->y + TILE_SIZE
			&& data->player.y + TILE_SIZE > current->y)
		{
			data->game_state = GAME_OVER;
			display_game_over(data);
			return (1);
		}
		current = current->next;
	}
	return (0);
}

void	handle_movement(int keycode, t_data *data, int *new_x, int *new_y)
{
	data->cur_input = 10;
	if (keycode == 53)
		exit_game(data);
	else if (is_movement_key(keycode))
		process_movement(keycode, data, new_x, new_y);
	else
		data->cur_input = -1;
}

int	exit_game(t_data *data)
{
	free_tiles(data);
	mlx_destroy_image(data->mlx_ptr, data->tilesheet_img);
	mlx_destroy_image(data->mlx_ptr, data->piece_tilesheet_img);
	free_player_frames(data);
	free_enemies(data);
	if (data->player_tilesheet_img)
		mlx_destroy_image(data->mlx_ptr, data->player_tilesheet_img);
	if (data->img)
		mlx_destroy_image(data->mlx_ptr, data->img);
	if (data->win_ptr)
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	free_map(data);
	exit(EXIT_SUCCESS);
	return (0);
}
