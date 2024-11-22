/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mm-furi <mm-furi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 17:19:38 by mm-furi           #+#    #+#             */
/*   Updated: 2024/11/15 14:21:03 by mm-furi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	draw_image_on_buffer(t_data *data, void *img, int x, int y)
{
	t_img_data		src;
	int				i;
	int				j;
	unsigned int	color;

	src.addr = mlx_get_data_addr(img, &src.bits_per_pixel, &src.line_length,
			&src.endian);
	j = 0;
	while (j < TILE_SIZE && (y + j) < WINDOW_HEIGHT)
	{
		i = 0;
		while (i < TILE_SIZE && (x + i) < WINDOW_WIDTH)
		{
			color = *(unsigned int *)(src.addr + j * src.line_length + i
					* (src.bits_per_pixel / 8));
			if ((color & 0xFF000000) != 0xFF000000)
				*(unsigned int *)(data->addr + ((y + j) * data->line_length + (x
								+ i) * (data->bits_per_pixel / 8))) = color;
			i++;
		}
		j++;
	}
}

void	draw_tile(t_data *data, char tile, int x, int y)
{
	int	screen_x;
	int	screen_y;

	screen_x = data->offset_x + x * TILE_SIZE;
	screen_y = data->offset_y + y * TILE_SIZE;
	if (tile == '1')
		draw_image_on_buffer(data, data->tile_images[WALL_TILE], screen_x,
			screen_y);
	else if (tile == '0' || tile == 'C' || tile == 'P')
		draw_image_on_buffer(data, data->tile_images[FLOOR_TILE], screen_x,
			screen_y);
	else if (tile == 'E')
	{
		draw_image_on_buffer(data, data->tile_images[FLOOR_TILE], screen_x,
			screen_y);
		if (data->collect_collecter == data->total_collect)
		{
			draw_image_on_buffer(data, data->tile_images[EXIT_TILE], screen_x,
				screen_y);
		}
	}
}

void	draw_map_row(t_data *data, int y)
{
	int		x;
	char	tile;

	x = 0;
	while (data->map[y][x])
	{
		tile = data->map[y][x];
		draw_tile(data, tile, x, y);
		x++;
	}
}

void	draw_map(t_data *data)
{
	int	y;

	data->offset_x = (WINDOW_WIDTH - (data->map_width * TILE_SIZE)) / 2;
	data->offset_y = (WINDOW_HEIGHT - (data->map_height * TILE_SIZE)) / 2;
	y = 0;
	while (data->map[y])
	{
		draw_map_row(data, y);
		y++;
	}
}

void	draw_enemies(t_data *data)
{
	t_enemy	*current;
	int		offset_x;
	int		offset_y;

	offset_x = (WINDOW_WIDTH - (data->map_width * TILE_SIZE)) / 2;
	offset_y = (WINDOW_HEIGHT - (data->map_height * TILE_SIZE)) / 2;
	current = data->enemies;
	while (current)
	{
		draw_image_on_buffer(data,
			current->frames[current->current_direction][current->current_frame],
			offset_x + current->x, offset_y + current->y);
		current = current->next;
	}
}
