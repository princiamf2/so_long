/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mm-furi <mm-furi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 13:59:43 by mm-furi           #+#    #+#             */
/*   Updated: 2024/11/14 13:44:46 by mm-furi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include "so_long.h"

char	*fft_strchr(const char *str, int c)
{
	while (*str)
	{
		if (*str == (char)c)
			return ((char *)str);
		str++;
	}
	if ((char)c == '\0')
		return ((char *)str);
	return (NULL);
}

char	*process_line(int fd, char **next_line)
{
	int	position;
	int	bytes_read;

	if (!next_line)
		return (NULL);
	bytes_read = 1;
	while (1)
	{
		position = find_newline_position(next_line[fd]);
		if (position != -1)
			return (ft_output(&next_line[fd], position));
		bytes_read = read_and_append(fd, &next_line[fd]);
		if (bytes_read == -1)
		{
			free(next_line[fd]);
			next_line[fd] = NULL;
			return (NULL);
		}
		if (bytes_read == 0)
			return (ft_output(&next_line[fd], -1));
	}
}

char	*ft_strndup(char *src, size_t n)
{
	size_t	i;
	char	*lol;

	if (!src)
		return (NULL);
	lol = (char *)malloc(n + 1);
	if (lol == NULL)
		return (NULL);
	i = 0;
	while (i < n && src[i] != '\0')
	{
		lol[i] = src[i];
		i++;
	}
	lol[i] = '\0';
	return (lol);
}

char	*ft_strnjoin(char *s1, const char *s2)
{
	char	*str;
	size_t	len1;
	size_t	len2;
	size_t	i;

	if (s1)
		len1 = ft_strlen(s1);
	else
		len1 = 0;
	len2 = ft_strlen(s2);
	str = (char *)malloc(len1 + len2 + 1);
	if (!str)
	{
		if (s1)
			free(s1);
		return (NULL);
	}
	if (s1)
		i = copy_and_free_s1(str, s1);
	else
		i = 0;
	copy_s2(str, s2, i);
	return (str);
}

int	read_and_append(int fd, char **next_line)
{
	char	buff[BUFFER_SIZE + 1];
	int		bytes;

	bytes = read(fd, buff, BUFFER_SIZE);
	if (bytes <= 0)
		return (bytes);
	buff[bytes] = '\0';
	*next_line = ft_strnjoin(*next_line, buff);
	if (!*next_line)
		return (-1);
	return (bytes);
}
