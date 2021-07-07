/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 15:21:31 by bahaas            #+#    #+#             */
/*   Updated: 2021/07/07 18:59:42 by bahaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	print_mssg(t_philo *philo, char *status, int i, int j)
{
	char	*time;
	char	*id;
	char	mssg[1000];

	time = ft_itoa(elapsed_time(philo->main->start_time));
	id = ft_itoa(philo->id);
	while (time[j])
		mssg[i++] = time[j++];
	mssg[i++] = 'm';
	mssg[i++] = 's';
	mssg[i++] = '\t';
	j = 0;
	while (id[j])
		mssg[i++] = id[j++];
	mssg[i++] = ' ';
	j = 0;
	while (status[j])
		mssg[i++] = status[j++];
	mssg[i] = '\0';
	pthread_mutex_lock(&philo->main->printer);
	if (!philo->main->dead_found)
		write(1, mssg, i);
	pthread_mutex_unlock(&philo->main->printer);
	free(id);
	free(time);
}

void	select_mssg(t_philo *philo)
{
	if (!philo->main->dead_found)
	{
		if (philo->status == TAKE_FORK)
			print_mssg(philo, "has taken a fork\n", 0, 0);
		else if (philo->status == EATING)
			print_mssg(philo, "is eating\n", 0, 0);
		else if (philo->status == SLEEPING)
			print_mssg(philo, "is sleeping\n", 0, 0);
		else if (philo->status == THINKING)
			print_mssg(philo, "is thinking\n", 0, 0);
		else if (philo->status == DEAD)
			print_mssg(philo, "died\n", 0, 0);
	}
}
