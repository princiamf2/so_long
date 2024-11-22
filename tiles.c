/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tiles.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mm-furi <mm-furi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 16:03:09 by mm-furi           #+#    #+#             */
/*   Updated: 2024/11/13 16:45:07 by mm-furi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	load_tiles(t_data *data)
{
	int	i;
	int	total_tiles;
	int	tile_x;
	int	tile_y;

	total_tiles = data->tiles_per_row * data->tiles_per_col;
	if (total_tiles <= EXIT_TILE)
	{
		write(2, "Erreur : le tileset ne contient pas assez de tuiles.\n", 52);
		exit_game(data);
	}
	data->tile_images = malloc(sizeof(void *) * total_tiles);
	if (!data->tile_images)
		return ;
	i = 0;
	while (i < total_tiles)
	{
		tile_x = i % data->tiles_per_row;
		tile_y = i / data->tiles_per_row;
		data->tile_images[i] = get_tile_images(data, tile_x, tile_y);
		if (!data->tile_images[i])
			write(2, "Erreur lors du chargement de la tuile\n", 39);
		i++;
	}
}

void	copy_pixel(t_img_data *tilesheet, t_img_data *tile, t_point src,
		t_point dest)
{
	char	*src_pixel;
	char	*dest_pixel;

	src_pixel = tilesheet->addr + (src.y * tilesheet->line_length) + (src.x
			* (tilesheet->bits_per_pixel / 8));
	dest_pixel = tile->addr + (dest.y * tile->line_length) + (dest.x
			* (tile->bits_per_pixel / 8));
	*(unsigned int *)dest_pixel = *(unsigned int *)src_pixel;
}

void	copy_tile_image(t_img_data *tilesheet, t_img_data *tile, int tile_x,
		int tile_y)
{
	int		x;
	int		y;
	t_point	src;
	t_point	dest;

	y = 0;
	while (y < TILE_SIZE)
	{
		x = 0;
		while (x < TILE_SIZE)
		{
			src.x = tile_x * TILE_SIZE + x;
			src.y = tile_y * TILE_SIZE + y;
			dest.x = x;
			dest.y = y;
			copy_pixel(tilesheet, tile, src, dest);
			x++;
		}
		y++;
	}
}

void	*get_tile_images(t_data *data, int tile_x, int tile_y)
{
	void		*tile_img;
	t_img_data	tilesheet;
	t_img_data	tile;

	tile_img = mlx_new_image(data->mlx_ptr, TILE_SIZE, TILE_SIZE);
	if (!tile_img)
		return (NULL);
	tilesheet.addr = mlx_get_data_addr(data->tilesheet_img,
			&tilesheet.bits_per_pixel, &tilesheet.line_length,
			&tilesheet.endian);
	tile.addr = mlx_get_data_addr(tile_img, &tile.bits_per_pixel,
			&tile.line_length, &tile.endian);
	copy_tile_image(&tilesheet, &tile, tile_x, tile_y);
	return (tile_img);
}

void	free_tiles(t_data *data)
{
	int	i;
	int	total_tiles;

	total_tiles = data->tiles_per_row * data->tiles_per_col;
	i = 0;
	while (i < total_tiles)
	{
		if (data->tile_images[i])
			mlx_destroy_image(data->mlx_ptr, data->tile_images[i]);
		i++;
	}
	free(data->tile_images);
}
