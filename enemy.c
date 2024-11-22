/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mm-furi <mm-furi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 14:10:41 by mm-furi           #+#    #+#             */
/*   Updated: 2024/11/18 15:09:56 by mm-furi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_enemy	*create_enemy(t_data *data, int x, int y)
{
	t_enemy	*new_enemy;

	new_enemy = (t_enemy *)malloc(sizeof(t_enemy));
	if (!new_enemy)
	{
		write(2, "Erreur d'allocation mémoire pour un ennemi\n", 43);
		exit_game(data);
	}
	new_enemy->x = x * TILE_SIZE;
	new_enemy->y = y * TILE_SIZE;
	new_enemy->current_direction = rand() % 4;
	new_enemy->current_frame = 0;
	new_enemy->next = NULL;
	return (new_enemy);
}

void	add_enemy(t_data *data, int x, int y)
{
	t_enemy	*new_enemy;
	t_enemy	*temp;

	new_enemy = create_enemy(data, x, y);
	if (!new_enemy)
		return ;
	if (!data->enemies)
		data->enemies = new_enemy;
	else
	{
		temp = data->enemies;
		while (temp->next)
			temp = temp->next;
		temp->next = new_enemy;
	}
	data->enemy_count++;
}

int	allocate_visited(t_data *data, int ***visited)
{
	int	y;

	*visited = (int **)malloc(sizeof(int *) * data->map_height);
	if (!*visited)
		return (-1);
	y = 0;
	while (y < data->map_height)
	{
		(*visited)[y] = (int *)malloc(sizeof(int) * data->map_width);
		if (!(*visited)[y])
		{
			free_visited(*visited, y);
			return (-1);
		}
		y++;
	}
	return (0);
}

void	free_visited(int **visited, int height)
{
	int	y;

	y = 0;
	while (y < height)
	{
		free(visited[y]);
		y++;
	}
	free(visited);
}

void	animate_enemies(t_data *data)
{
	static int	time = 0;
	t_enemy		*current;

	if (time++ >= ANIMATION_SPEED)
	{
		current = data->enemies;
		while (current)
		{
			current->current_frame = (current->current_frame + 1) % 3;
			current = current->next;
		}
		time = 0;
	}
}
