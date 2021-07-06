/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 23:44:13 by bahaas            #+#    #+#             */
/*   Updated: 2021/07/06 23:44:16 by bahaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	ft_len_nbr(long n)
{
	unsigned int	size;

	size = 1;
	while (n >= 10)
	{
		n = n / 10;
		size++;
	}
	return (size);
}

char	*ft_itoa(long n)
{
	char	*str;
	int		size;
	int		i;

	i = 0;
	size = ft_len_nbr(n);
	str = (char *)malloc(size + 1);
	if (!str)
		return (NULL);
	str[size] = '\0';
	while (size > i)
	{
		size--;
		str[size] = (n % 10) + '0';
		n /= 10;
	}
	return (str);
}

void	ft_putstr_fd(char *s, int fd)
{
	int		i;

	i = 0;
	if (s)
	{
		while (s[i])
		{
			write(fd, &s[i], 1);
			i++;
		}
	}
}

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

void		ft_bzero(void *s, size_t n)
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

char		*ft_strjoin(char const *s1, char const *s2)
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
	return (str);
}

void	print_mssg(t_philo *philo, char *state)
{
	char *time;
	char *id;
	char *mssg;

	time = ft_itoa(elapsed_time(philo->main->start_time));
	id = ft_itoa(philo->num);
	mssg = ft_strjoin(time, "ms\t");
	mssg = ft_strjoin(mssg, id);
	mssg = ft_strjoin(mssg, " ");
	mssg = ft_strjoin(mssg, state);
	pthread_mutex_lock(&philo->main->printer);
	ft_putstr_fd(mssg,1);
	pthread_mutex_unlock(&philo->main->printer);
	free(time);
	free(id);
	free(mssg);
}

void	select_mssg(t_philo *philo)
{
	if(!philo->main->dead_found)
	{
		if(philo->state == TAKE_FORK)
			print_mssg(philo, "has taken a fork\n");
		else if(philo->state == EATING)
			print_mssg(philo, "is eating\n");
		else if(philo->state == SLEEPING)
			print_mssg(philo, "is sleeping\n");
		else if(philo->state == THINKING)
			print_mssg(philo, "is thinking\n");
		else if(philo->state == DEAD)
			print_mssg(philo, "died\n");
	}
}
