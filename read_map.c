/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mm-furi <mm-furi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 11:10:00 by mm-furi           #+#    #+#             */
/*   Updated: 2024/11/18 16:57:07 by mm-furi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	count_map_height(char *filename, int *map_height)
{
	int		fd;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror("Erreur lors de l'ouverture du fichier de carte");
		return (-1);
	}
	*map_height = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		(*map_height)++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (0);
}

int	allocate_map(t_data *data)
{
	data->map = malloc(sizeof(char *) * (data->map_height + 1));
	if (!data->map)
	{
		write(2, "Erreur d'allocation mémoire pour la carte\n", 42);
		return (-1);
	}
	return (0);
}

int	read_map_lines(t_data *data, char *filename)
{
	int		fd;
	char	*line;
	int		y;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror("Erreur lors de la réouverture du fichier de carte");
		return (-1);
	}
	y = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		data->map[y++] = line;
		line = get_next_line(fd);
	}
	data->map[y] = NULL;
	close(fd);
	return (0);
}

int	read_map(t_data *data, char *filename)
{
	if (count_map_height(filename, &data->map_height) == -1)
		return (-1);
	if (data->map_height == 0)
	{
		write(2, "Erreur : la carte est vide\n", 27);
		return (-1);
	}
	if (allocate_map(data) == -1)
		return (-1);
	if (read_map_lines(data, filename) == -1)
	{
		free(data->map);
		return (-1);
	}
	if (!data->map)
	{
		ft_putstr_fd("Erreur : data->map est NULL après read_map\n", 2);
		return (-1);
	}
	return (0);
}
