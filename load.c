/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mm-furi <mm-furi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 17:10:49 by mm-furi           #+#    #+#             */
/*   Updated: 2024/11/18 17:54:31 by mm-furi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	reinit_map(t_data *data)
{
	int	i;

	if (!data->map)
	{
		ft_putstr_fd("Erreur : data->map est NULL dans reinit_map\n", 2);
		return (-1);
	}
	data->map_initial = malloc(sizeof(char *) * (data->map_height + 1));
	if (!data->map_initial)
		return (-1);
	i = 0;
	while (data->map[i])
	{
		data->map_initial[i] = ft_strdup(data->map[i]);
		if (!data->map_initial[i])
			return (-1);
		i++;
	}
	data->map_initial[i] = NULL;
	return (0);
}

int	load_map(t_data *data, char *filename)
{
	if (read_map(data, filename) == -1)
		return (-1);
	if (!data->map)
	{
		ft_putstr_fd("Erreur : la carte n'a pas été lue correctement\n", 2);
		return (-1);
	}
	if (validate_map(data) == -1)
		return (-1);
	if (check_empty_map(data) == -1)
		return (-1);
	count_collectibles(data);
	data->cur_input = -1;
	if (reinit_map(data) == -1)
	{
		ft_putstr_fd("Erreur : la carte n'a pas pu être réinitialisée\n", 2);
		return (-1);
	}
	initialize_enemies(data);
	return (0);
}

int	load_resources(t_data *data, char *map_file)
{
	if (load_map_and_tiles(data, map_file) == -1)
		return (-1);
	if (load_images(data) == -1)
		return (-1);
	if (load_frames(data) == -1)
		return (-1);
	if (load_gameover_img(data) == -1)
		return (-1);
	return (0);
}

int	load_images(t_data *data)
{
	if (load_player_tilesheet(data) == -1)
		return (-1);
	if (load_piece_tilesheet(data) == -1)
		return (-1);
	if (load_enemy_tilesheet(data) == -1)
		return (-1);
	srand(time(NULL));
	return (0);
}

int	load_frames(t_data *data)
{
	if (load_player_frames(data) == -1)
		return (-1);
	if (load_collect_frames(data) == -1)
		return (-1);
	if (load_enemy_frames(data) == -1)
		return (-1);
	return (0);
}
