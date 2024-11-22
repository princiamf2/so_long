/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_enemies.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mm-furi <mm-furi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 17:26:10 by mm-furi           #+#    #+#             */
/*   Updated: 2024/11/13 17:26:53 by mm-furi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	move_enemy(t_data *data, t_enemy *enemy)
{
	int	new_x;
	int	new_y;

	update_enemy_direction(enemy);
	calculate_new_position(enemy, &new_x, &new_y);
	if (is_move_valid(data, new_x, new_y))
	{
		enemy->x = new_x;
		enemy->y = new_y;
	}
	else
	{
		enemy->current_direction = rand() % 4;
	}
}

void	move_enemies(t_data *data)
{
	t_enemy	*current;

	current = data->enemies;
	while (current)
	{
		move_enemy(data, current);
		current = current->next;
	}
}
