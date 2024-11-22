/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_tilesheet.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mm-furi <mm-furi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 16:37:36 by mm-furi           #+#    #+#             */
/*   Updated: 2024/11/13 16:41:58 by mm-furi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	load_tilesheet(t_data *data, char *path)
{
	data->tilesheet_img = mlx_xpm_file_to_image(data->mlx_ptr, path,
			&data->img_width, &data->img_height);
	if (!data->tilesheet_img)
	{
		write(2, "Erreur lors du chargement de la tilesheet\n", 44);
		return (-1);
	}
	data->tiles_per_row = data->img_width / TILE_SIZE;
	data->tiles_per_col = data->img_height / TILE_SIZE;
	return (0);
}

int	load_map_and_tiles(t_data *data, char *map_file)
{
	if (load_map(data, map_file) == -1)
		return (-1);
	if (load_tilesheet(data, "src/tilesheets/tileset.xpm") == -1)
		return (-1);
	load_tiles(data);
	return (0);
}

int	load_player_tilesheet(t_data *data)
{
	data->player_tilesheet_img = mlx_xpm_file_to_image(data->mlx_ptr,
			"src/tilesheets/perso.xpm", &data->img_width, &data->img_height);
	if (!data->player_tilesheet_img)
	{
		write(2, "Erreur lors du chargement de la tilesheet du joueur\n", 53);
		return (-1);
	}
	return (0);
}

int	load_piece_tilesheet(t_data *data)
{
	data->piece_tilesheet_img = mlx_xpm_file_to_image(data->mlx_ptr,
			"src/tilesheets/piece.xpm", &data->img_piece_width,
			&data->img_piece_height);
	if (!data->piece_tilesheet_img)
	{
		write(2, "Erreur lors du chargement de la tilesheet du collectable\n",
			53);
		return (-1);
	}
	return (0);
}

int	load_enemy_tilesheet(t_data *data)
{
	data->enemy_tilesheet_img = mlx_xpm_file_to_image(data->mlx_ptr,
			"src/tilesheets/enemy.xpm", &data->img_enemy_width,
			&data->img_enemy_height);
	if (!data->enemy_tilesheet_img)
	{
		write(2, "Erreur lors du chargement de la tilesheet des ennemis\n", 54);
		return (-1);
	}
	return (0);
}
