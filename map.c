/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mm-furi <mm-furi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 16:26:24 by mm-furi           #+#    #+#             */
/*   Updated: 2024/11/18 16:53:34 by mm-furi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	find_player_position(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (data->map[y])
	{
		x = 0;
		while (data->map[y][x])
		{
			if (data->map[y][x] == 'P')
			{
				data->player.tile_x = x;
				data->player.tile_y = y;
				data->player.x = x * TILE_SIZE;
				data->player.y = y * TILE_SIZE;
				return (0);
			}
			x++;
		}
		y++;
	}
	write(2, "Erreur : position du joueur non trouvée\n", 40);
	return (-1);
}

void	draw_player(t_data *data)
{
	int	offset_x;
	int	offset_y;
	int	current_frame;
	int	current_dir;

	current_dir = data->player.current_direction;
	current_frame = data->player.current_frame;
	offset_x = (WINDOW_WIDTH - (data->map_width * TILE_SIZE)) / 2;
	offset_y = (WINDOW_HEIGHT - (data->map_height * TILE_SIZE)) / 2;
	draw_image_on_buffer(data,
		data->player.frames[current_dir][current_frame],
		offset_x + data->player.x, offset_y + data->player.y);
}

void	draw_collects(t_data *data)
{
	int		x;
	int		y;
	char	tile;
	int		offset_x;
	int		offset_y;

	offset_x = (WINDOW_WIDTH - (data->map_width * TILE_SIZE)) / 2;
	offset_y = (WINDOW_HEIGHT - (data->map_height * TILE_SIZE)) / 2;
	y = 0;
	while (y < data->map_height)
	{
		x = 0;
		while (x < data->map_width)
		{
			tile = data->map[y][x];
			if (tile == 'C')
			{
				draw_image_on_buffer(data,
					data->piece.frame[data->piece.current_frame], offset_x + x
					* TILE_SIZE, offset_y + y * TILE_SIZE);
			}
			x++;
		}
		y++;
	}
}

void	game_state(t_data *data)
{
	int	x;
	int	y;

	if (data->game_state == GAME_OVER)
	{
		mlx_clear_window(data->mlx_ptr, data->win_ptr);
		x = (WINDOW_WIDTH - data->img_gameover_width) / 2;
		y = (WINDOW_HEIGHT - data->img_gameover_height) / 2;
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
			data->img_gameover, x, y);
		data->blink_counter++;
		if ((data->blink_counter / 30) % 2 == 0)
		{
			mlx_string_put(data->mlx_ptr, data->win_ptr, WINDOW_WIDTH / 2 - 120,
				WINDOW_HEIGHT / 2 + data->img_gameover_height / 2 + 20,
				0xFFFFFF, "Appuyez sur Espace pour recommencer");
		}
	}
	else
		data->blink_counter = 0;
}

int	render_map(t_data *data)
{
	game_state(data);
	if (data->game_state == GAME_OVER)
		return (0);
	ft_memset(data->addr, 0, WINDOW_HEIGHT * data->line_length);
	draw_and_animate_elements(data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img, 0, 0);
	if (display_move_count(data) == -1)
		return (-1);
	return (0);
}
