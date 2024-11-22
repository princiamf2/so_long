/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mm-furi <mm-furi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 16:42:32 by mm-furi           #+#    #+#             */
/*   Updated: 2024/11/18 17:03:50 by mm-furi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_current_map(t_data *data)
{
	int	i;

	if (data->map)
	{
		i = 0;
		while (data->map[i])
		{
			free(data->map[i]);
			i++;
		}
		free(data->map);
		data->map = NULL;
	}
	else
	{
		ft_putstr_fd("Erreur : data->map est NULL dans free_current_map\n", 2);
	}
}

int	copy_initial_map(t_data *data)
{
	int	i;

	if (!data->map_initial)
		return (-1);
	data->map = malloc(sizeof(char *) * (data->map_height + 1));
	if (!data->map)
	{
		ft_putstr_fd("Erreur : allocation de data->map a échoué\n", 2);
		return (-1);
	}
	i = 0;
	while (data->map_initial[i])
	{
		data->map[i] = ft_strdup(data->map_initial[i]);
		if (!data->map[i])
		{
			ft_putstr_fd("Erreur : ft_strdup a échoué\n", 2);
			return (-1);
		}
		i++;
	}
	data->map[i] = NULL;
	return (0);
}

int	display_move_count(t_data *data)
{
	char	*move_count_str;
	char	*message;

	move_count_str = ft_itoa(data->move_count);
	if (!move_count_str)
		return (-1);
	message = ft_strjoin("Nombre de mouvements : ", move_count_str);
	free(move_count_str);
	if (!message)
		return (-1);
	mlx_string_put(data->mlx_ptr, data->win_ptr, 10, 10, 0xFFFFFF, message);
	free(message);
	return (0);
}

void	draw_and_animate_elements(t_data *data)
{
	draw_map(data);
	draw_player(data);
	draw_collects(data);
	draw_enemies(data);
	animate_collect(data);
	animate_player(data);
	animate_enemies(data);
	move_enemies(data);
}
