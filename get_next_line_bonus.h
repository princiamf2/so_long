/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mm-furi <mm-furi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 14:05:06 by mm-furi           #+#    #+#             */
/*   Updated: 2024/11/14 13:38:24 by mm-furi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# include <limits.h>
# include <stdint.h>
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

char	*ft_strndup(char *src, size_t n);
void	ft_free(char **s);
int		ft_strlen(const char *str);
void	*ft_calloc(size_t i, size_t c);
char	*fft_strchr(const char *str, int c);
char	*ft_strnjoin(char *s1, const char *s2);
char	*ft_update_nl(char **next_line, int position);
char	*ft_output(char **next_line, int position);
char	*get_next_line(int fd);
int		read_and_append(int fd, char **next_line);
int		find_newline_position(char *str);
char	*process_line(int fd, char **next_line);
char	*extract_line(char **next_line, int position);
int		update_buffer(char **next_line, int position);
#endif