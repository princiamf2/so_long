/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mm-furi <mm-furi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 17:13:18 by mm-furi           #+#    #+#             */
/*   Updated: 2024/11/18 18:49:27 by mm-furi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	check_unreachable(t_data *data, int **visited)
{
	int	x;
	int	y;

	y = 0;
	while (y < data->map_height)
	{
		x = 0;
		while (x < data->map_width)
		{
			if ((data->map[y][x] == 'C' || data->map[y][x] == 'E')
				&& !visited[y][x])
				return (-1);
			x++;
		}
		y++;
	}
	return (0);
}

int	check_rectangular_map(t_data *data)
{
	size_t	width;
	int		y;

	if (!data->map || !data->map[0])
	{
		ft_putstr_fd("Erreur : la carte est vide ou invalide\n", 2);
		return (-1);
	}
	width = ft_strlen(data->map[0]);
	y = 1;
	while (y < data->map_height)
	{
		if (ft_strlen(data->map[y]) != (int)width)
		{
			ft_putstr_fd("Erreur : la carte n'est pas rectangulaire\n", 2);
			return (-1);
		}
		y++;
	}
	data->map_width = width;
	return (0);
}

int	check_empty_map(t_data *data)
{
	if (data->map_height == 0)
	{
		ft_putstr_fd("Erreur : la carte est vide\n", 2);
		return (-1);
	}
	return (0);
}

void	count_collectibles(t_data *data)
{
	int	x;
	int	y;

	data->total_collect = 0;
	data->collect_collecter = 0;
	y = 0;
	while (y < data->map_height)
	{
		x = 0;
		while (x < data->map_width)
		{
			if (data->map[y][x] == 'C')
				data->total_collect++;
			x++;
		}
		y++;
	}
}
