/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mm-furi <mm-furi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 14:49:44 by mm-furi           #+#    #+#             */
/*   Updated: 2024/11/19 14:41:00 by mm-furi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	init_mlx(t_data *data)
{
	data->mlx_ptr = mlx_init();
	if (!data->mlx_ptr)
	{
		write(2, "Erreur lors de l'initialisation de MLX\n", 40);
		return (-1);
	}
	data->win_ptr = mlx_new_window(data->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT,
			"so_long");
	if (!data->win_ptr)
	{
		write(2, "Erreur lors de la création de la fenêtre\n", 42);
		return (-1);
	}
	return (0);
}

void	init_enemies(t_data *data)
{
	t_enemy	*current;

	current = data->enemies;
	while (current)
	{
		current->current_direction = rand() % 4;
		current->current_frame = 0;
		current = current->next;
	}
}

void	initialize_visited_rows(t_data *data, int **visited)
{
	int	y;
	int	x;

	y = 0;
	while (y < data->map_height)
	{
		x = 0;
		while (x < data->map_width)
		{
			visited[y][x] = 0;
			x++;
		}
		y++;
	}
}

int	initialize_visited(t_data *data, int ***visited)
{
	if (allocate_visited(data, visited) == -1)
		return (-1);
	initialize_visited_rows(data, *visited);
	return (0);
}
