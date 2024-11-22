/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mm-furi <mm-furi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 13:50:16 by mm-furi           #+#    #+#             */
/*   Updated: 2024/11/14 13:16:40 by mm-furi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include "so_long.h"

void	ft_free(char **s)
{
	free(*s);
	*s = NULL;
}

int	find_newline_position(char *str)
{
	char	*ptr;

	if (str)
	{
		ptr = fft_strchr(str, '\n');
		if (ptr)
			return (ptr - str);
	}
	return (-1);
}

char	*ft_update_nl(char **next_line, int position)
{
	char	*tmp;
	int		len;

	len = ft_strlen(*next_line) - position;
	tmp = ft_strndup(*next_line + position, len);
	ft_free(next_line);
	return (tmp);
}

char	*ft_output(char **next_line, int position)
{
	char	*line;

	line = extract_line(next_line, position);
	if (!line)
		return (NULL);
	if (update_buffer(next_line, position) == -1)
	{
		free(line);
		return (NULL);
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*next_line[OPEN_MAX];

	if (BUFFER_SIZE <= 0 || fd < 0 || fd >= OPEN_MAX)
		return (NULL);
	return (process_line(fd, next_line));
}
