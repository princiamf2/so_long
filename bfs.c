/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mm-furi <mm-furi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 16:43:15 by mm-furi           #+#    #+#             */
/*   Updated: 2024/11/13 16:46:08 by mm-furi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	dequeue(t_queue **front, t_queue **rear, int *x, int *y)
{
	t_queue	*temp;

	temp = *front;
	if (!*front)
		return (0);
	*x = temp->x;
	*y = temp->y;
	*front = temp->next;
	if (!*front)
		*rear = NULL;
	free(temp);
	return (1);
}

void	enqueue(t_queue **front, t_queue **rear, int x, int y)
{
	t_queue	*new_node;

	new_node = (t_queue *)malloc(sizeof(t_queue));
	if (!new_node)
		return ;
	new_node->x = x;
	new_node->y = y;
	new_node->next = NULL;
	if (*rear)
		(*rear)->next = new_node;
	else
		*front = new_node;
	*rear = new_node;
}

void	explore_neighbors(t_data *data, int **visited, t_queue_info *queue_info,
		t_point pos)
{
	int			new_x;
	int			new_y;
	int			i;
	static int	dir_x[4] = {0, 0, -1, 1};
	static int	dir_y[4] = {-1, 1, 0, 0};

	i = 0;
	while (i < 4)
	{
		new_x = pos.x + dir_x[i];
		new_y = pos.y + dir_y[i];
		if (new_x >= 0 && new_x < data->map_width && new_y >= 0
			&& new_y < data->map_height && !visited[new_y][new_x]
			&& data->map[new_y][new_x] != '1')
		{
			enqueue(&(queue_info->front), &(queue_info->rear), new_x, new_y);
			visited[new_y][new_x] = 1;
		}
		i++;
	}
}

void	bfs_search(t_data *data, int **visited, int player_x, int player_y)
{
	t_queue_info	queue_info;
	t_point			pos;

	queue_info.front = NULL;
	queue_info.rear = NULL;
	pos.x = player_x;
	pos.y = player_y;
	enqueue(&(queue_info.front), &(queue_info.rear), pos.x, pos.y);
	visited[pos.y][pos.x] = 1;
	while (queue_info.front)
	{
		if (!dequeue(&(queue_info.front), &(queue_info.rear), &pos.x, &pos.y))
			break ;
		explore_neighbors(data, visited, &queue_info, pos);
	}
}

int	check_path(t_data *data)
{
	int	**visited;
	int	player_x;
	int	player_y;

	player_x = data->player.tile_x;
	player_y = data->player.tile_y;
	if (player_x < 0 || player_y < 0)
		return (-1);
	if (initialize_visited(data, &visited) == -1)
		return (-1);
	bfs_search(data, visited, player_x, player_y);
	if (check_unreachable(data, visited) == -1)
	{
		free_visited(visited, data->map_height);
		return (-1);
	}
	free_visited(visited, data->map_height);
	return (0);
}
