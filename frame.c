/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mm-furi <mm-furi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 17:23:23 by mm-furi           #+#    #+#             */
/*   Updated: 2024/11/19 15:11:45 by mm-furi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	copy_frame_pixels(t_img_data *src, t_img_data *dst, int src_x,
		int src_y)
{
	int	i;
	int	j;
	int	src_pos;
	int	dst_pos;

	j = 0;
	while (j < TILE_SIZE)
	{
		i = 0;
		while (i < TILE_SIZE)
		{
			src_pos = (src_y + j) * src->line_length + (src_x + i)
				* (src->bits_per_pixel / 8);
			dst_pos = j * dst->line_length + i * (dst->bits_per_pixel / 8);
			*(unsigned int *)(dst->addr + dst_pos) = *(unsigned int *)(src->addr
					+ src_pos);
			i++;
		}
		j++;
	}
}

void	*extract_frame(t_data *data, void *source_img, int x, int y)
{
	void		*frame_img;
	t_img_data	src;
	t_img_data	dst;

	frame_img = mlx_new_image(data->mlx_ptr, TILE_SIZE, TILE_SIZE);
	if (!frame_img)
		return (NULL);
	src.addr = mlx_get_data_addr(source_img, &src.bits_per_pixel,
			&src.line_length, &src.endian);
	dst.addr = mlx_get_data_addr(frame_img, &dst.bits_per_pixel,
			&dst.line_length, &dst.endian);
	copy_frame_pixels(&src, &dst, x, y);
	return (frame_img);
}

int	load_player_frames(t_data *data)
{
	int	dir;
	int	frame;
	int style_perso_x = 6 * TILE_SIZE;
	int style_perso_y = 4 * TILE_SIZE;

	dir = 0;
	while (dir < 4)
	{
		frame = 0;
		while (frame < 3)
		{
			data->player.frames[dir][frame] = extract_frame(data,
					data->player_tilesheet_img, frame * TILE_SIZE + style_perso_x, dir
					* TILE_SIZE + style_perso_y);
			if (!data->player.frames[dir][frame])
				return (-1);
			frame++;
		}
		dir++;
	}
	return (0);
}

int	load_enemy_frames(t_data *data)
{
	t_enemy	*current;
	int		dir;
	int		frame;

	current = data->enemies;
	while (current)
	{
		dir = 0;
		while (dir < 4)
		{
			frame = 0;
			while (frame < 3)
			{
				current->frames[dir][frame] = extract_frame(data,
						data->enemy_tilesheet_img, frame * TILE_SIZE + 6 * TILE_SIZE, dir
						* TILE_SIZE + 4 * TILE_SIZE);
				if (!current->frames[dir][frame])
					return (-1);
				frame++;
			}
			dir++;
		}
		current = current->next;
	}
	return (0);
}

int	load_collect_frames(t_data *data)
{
	int	frame;

	frame = 0;
	while (frame < 6)
	{
		data->piece.frame[frame] = extract_frame(data,
				data->piece_tilesheet_img, frame * TILE_SIZE, 0);
		if (!data->piece.frame[frame])
			return (-1);
		frame++;
	}
	return (0);
}
