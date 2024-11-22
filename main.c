/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mm-furi <mm-furi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 15:19:42 by mm-furi           #+#    #+#             */
/*   Updated: 2024/11/18 16:44:36 by mm-furi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	initialize_hooks(t_data *data)
{
	mlx_hook(data->win_ptr, 2, 1L << 0, key_press, data);
	mlx_hook(data->win_ptr, 17, 0L, exit_game, data);
	mlx_loop_hook(data->mlx_ptr, render_map, data);
	return (0);
}

int	reset_map(t_data *data)
{
	free_current_map(data);
	if (copy_initial_map(data) == -1)
		return (-1);
	return (0);
}

void	start_game_loop(t_data *data)
{
	mlx_loop(data->mlx_ptr);
}

int	check_map_name(int ac, char **av)
{
	int		i;
	int		j;
	char	*cible;

	j = 0;
	cible = ".ber";
	if (ac == 2)
	{
		i = ft_strlen(av[1]) - 4;
		while (cible[j])
		{
			if (av[1][i] != cible[j])
			{
				ft_putstr_fd("Erreur : la map est pas en .ber", 2);
				return (-1);
			}
			i++;
			j++;
		}
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac != 2)
	{
		write(2, "Usage: ./so_long <map_file>\n", 28);
		return (EXIT_FAILURE);
	}
	if (check_map_name(ac, av) == -1)
		return (EXIT_FAILURE);
	if (initialize_data(&data) == -1)
		return (EXIT_FAILURE);
	if (init_mlx(&data) == -1)
		return (EXIT_FAILURE);
	if (load_resources(&data, av[1]) == -1)
		return (EXIT_FAILURE);
	if (initialize_game(&data) == -1)
		return (EXIT_FAILURE);
	if (initialize_hooks(&data) == -1)
		return (EXIT_FAILURE);
	start_game_loop(&data);
	return (EXIT_SUCCESS);
}
