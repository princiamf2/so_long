/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mm-furi <mm-furi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 13:14:53 by mm-furi           #+#    #+#             */
/*   Updated: 2024/11/14 17:04:17 by mm-furi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include "so_long.h"

char	*extract_line(char **next_line, int position)
{
	char	*line;
	int		len;

	if (!next_line || !(*next_line))
		return (NULL);
	if (position == -1)
		len = ft_strlen(*next_line);
	else
		len = position;
	line = ft_strndup(*next_line, len);
	if (!line)
	{
		ft_putstr_fd("extract_line: ft_strndup a échoué\n", 2);
		return (NULL);
	}
	return (line);
}

int	update_buffer(char **next_line, int position)
{
	char	*new_buffer;

	if (position != -1 && (*next_line)[position] != '\0')
	{
		new_buffer = ft_update_nl(next_line, position + 1);
		if (!new_buffer)
		{
			ft_putstr_fd("update_buffer: ft_update_nl a échoué\n", 2);
			return (-1);
		}
		*next_line = new_buffer;
	}
	else
	{
		free(*next_line);
		*next_line = NULL;
	}
	return (0);
}

size_t	copy_and_free_s1(char *str, char *s1)
{
	size_t	i;

	i = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	free(s1);
	return (i);
}

void	copy_s2(char *str, const char *s2, size_t i)
{
	size_t	j;

	j = 0;
	while (s2[j])
	{
		str[i + j] = s2[j];
		j++;
	}
	str[i + j] = '\0';
}
