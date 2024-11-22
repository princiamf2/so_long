/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valide_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mm-furi <mm-furi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 12:06:51 by mm-furi           #+#    #+#             */
/*   Updated: 2024/11/18 19:17:05 by mm-furi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	check_walls(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < data->map_height)
	{
		x = 0;
		while (x < data->map_width)
		{
			if ((y == 0 || y == data->map_height - 1) && data->map[y][x] != '1')
			{
				ft_putstr_fd("les murs de la carte ne sont pas correct\n", 2);
				return (-1);
			}
			if ((x == 0 || x == data->map_width - 1) && data->map[y][x] != '1')
			{
				ft_putstr_fd("les murs de la carte ne sont pas correct\n", 2);
				return (-1);
			}
			x++;
		}
		y++;
	}
	return (0);
}

int	count_map_elements(t_data *data, int *player_count, int *exit_count,
		int *collect_count)
{
	int	x;
	int	y;

	*player_count = 0;
	*exit_count = 0;
	*collect_count = 0;
	y = 0;
	while (y < data->map_height)
	{
		x = 0;
		while (x < data->map_width)
		{
			if (data->map[y][x] == 'P')
				(*player_count)++;
			else if (data->map[y][x] == 'E')
				(*exit_count)++;
			else if (data->map[y][x] == 'C')
				(*collect_count)++;
			x++;
		}
		y++;
	}
	return (0);
}

int	validate_counts(int player_count, int exit_count, int collect_count)
{
	if (player_count != 1)
	{
		ft_putstr_fd("Erreur : il doit y avoir exactement un joueur (P)\n", 2);
		return (-1);
	}
	if (exit_count != 1)
	{
		ft_putstr_fd("Erreur : il doit y avoir une seul sortie (E)\n", 2);
		return (-1);
	}
	if (collect_count < 1)
	{
		ft_putstr_fd("Erreur : il doit y avoir au moins un collectable (C)\n",
			2);
		return (-1);
	}
	return (0);
}

int	check_unknown_chars(t_data *data)
{
	int		x;
	int		y;
	char	c;

	y = 0;
	while (y < data->map_height)
	{
		x = 0;
		while (x < data->map_width)
		{
			c = data->map[y][x];
			if (c != '0' && c != '1' && c != 'P' && c != 'E' && c != 'C'
				&& c != 'M')
			{
				write(2, "Erreur : caractère inconnu dans la carte\n", 41);
				return (-1);
			}
			x++;
		}
		y++;
	}
	return (0);
}

int	validate_map(t_data *data)
{
	int	player_count;
	int	exit_count;
	int	collect_count;

	if (check_rectangular_map(data) == -1)
		return (-1);
	if (check_unknown_chars(data) == -1)
		return (-1);
	if (check_walls(data) == -1)
		return (-1);
	if (count_map_elements(data, &player_count, &exit_count, &collect_count)
		== -1)
		return (-1);
	if (validate_counts(player_count, exit_count, collect_count) == -1)
		return (-1);
	if (find_player_position(data) == -1)
		return (-1);
	if (check_path(data) == -1)
	{
		ft_putstr_fd("pas de chemin", 2);
		return (-1);
	}
	return (0);
}
