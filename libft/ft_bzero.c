/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mm-furi <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 11:03:09 by mm-furi           #+#    #+#             */
/*   Updated: 2024/10/01 11:52:31 by mm-furi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_bzero(void *s, size_t n)
{
	unsigned char	*s2;
	size_t			i;

	s2 = s;
	i = 0;
	while (i < n)
	{
		s2[i] = 0;
		i++;
	}
	return (s);
}
