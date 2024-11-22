/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_over.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mm-furi <mm-furi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 14:42:07 by mm-furi           #+#    #+#             */
/*   Updated: 2024/11/18 16:32:41 by mm-furi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	display_game_over(t_data *data)
{
	int	x;
	int	y;

	x = (WINDOW_WIDTH - data->img_gameover_width) / 2;
	y = (WINDOW_HEIGHT - data->img_gameover_height) / 2;
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img_gameover, x,
		y);
	mlx_string_put(data->mlx_ptr, data->win_ptr, x, y
		+ data->img_gameover_height + 20, 0xFFFFFF,
		"Appuyez sur Espace pour recommencer");
	data->game_state = GAME_OVER;
}

int	load_gameover_img(t_data *data)
{
	int	width;
	int	height;

	data->img_gameover = mlx_xpm_file_to_image(data->mlx_ptr,
			"src/gameover.xpm", &width, &height);
	if (!data->img_gameover)
	{
		ft_putstr_fd("Erreur lors du chargement de l'image Game Over\n", 2);
		return (-1);
	}
	data->img_gameover_width = width;
	data->img_gameover_height = height;
	return (0);
}

static int	reset_player(t_data *data)
{
	if (find_player_position(data) == -1)
	{
		ft_putstr_fd("Joueur non trouvé après réinitialisation\n", 2);
		return (-1);
	}
	data->player.x = data->player.tile_x * TILE_SIZE;
	data->player.y = data->player.tile_y * TILE_SIZE;
	data->move_count = 0;
	data->collect_collecter = 0;
	data->blink_counter = 0;
	return (0);
}

static int	reset_enemies(t_data *data)
{
	free_enemies(data);
	initialize_enemies(data);
	if (load_enemy_frames(data) == -1)
	{
		ft_putstr_fd("Erreur lors du rechargement des frames des ennemis\n", 2);
		return (-1);
	}
	return (0);
}

int	reset_game(t_data *data)
{
	if (reset_map(data) == -1)
	{
		ft_putstr_fd("Erreur lors de la réinitialisation de la carte\n", 2);
		return (-1);
	}
	if (reset_player(data) == -1)
		return (-1);
	if (reset_enemies(data) == -1)
		return (-1);
	data->game_state = PLAYING;
	mlx_clear_window(data->mlx_ptr, data->win_ptr);
	render_map(data);
	return (0);
}
