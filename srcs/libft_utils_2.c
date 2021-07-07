/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 15:02:29 by bahaas            #+#    #+#             */
/*   Updated: 2021/07/07 15:32:20 by bahaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

size_t	ft_strlen(const char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	ft_bzero(void *s, size_t n)
{
	size_t		i;

	i = 0;
	while (i < n)
		((char *)s)[i++] = '\0';
}

static char	*ft_strcpy_join(char *dest, const char *src)
{
	size_t	i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = 0;
	return (dest);
}

static char	*ft_strncat_join(char *dest, const char *src, size_t n)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (dest[i])
		i++;
	j = 0;
	while (src[j] && j < n)
		dest[i++] = src[j++];
	dest[i] = 0;
	return (dest);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	size_t	len_s1_s2;
	size_t	i;

	i = 0;
	if (!s1 || !s2)
		return (NULL);
	len_s1_s2 = ft_strlen(s1) + ft_strlen(s2) + 1;
	str = (char *)malloc(sizeof(char) * (len_s1_s2));
	if (!str)
		return (NULL);
	ft_bzero(str, len_s1_s2);
	ft_strcpy_join(str, s1);
	ft_strncat_join(str, s2, ft_strlen(s2));
	free(s1);
	return (str);
}
