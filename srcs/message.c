/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 15:21:31 by bahaas            #+#    #+#             */
/*   Updated: 2021/07/07 15:34:30 by bahaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	print_mssg(t_philo *philo, char *state)
{
	char	*time;
	char	*id;
	char	*mssg;

	time = ft_itoa(elapsed_time(philo->main->start_time));
	id = ft_itoa(philo->num);
	mssg = ft_strjoin(time, "ms\t");
	mssg = ft_strjoin(mssg, id);
	mssg = ft_strjoin(mssg, " ");
	mssg = ft_strjoin(mssg, state);
	pthread_mutex_lock(&philo->main->printer);
	ft_putstr_fd(mssg, 1);
	pthread_mutex_unlock(&philo->main->printer);
	free(id);
	free(mssg);
}

void	select_mssg(t_philo *philo)
{
	if (!philo->main->dead_found)
	{
		if (philo->state == TAKE_FORK)
			print_mssg(philo, "has taken a fork\n");
		else if (philo->state == EATING)
			print_mssg(philo, "is eating\n");
		else if (philo->state == SLEEPING)
			print_mssg(philo, "is sleeping\n");
		else if (philo->state == THINKING)
			print_mssg(philo, "is thinking\n");
		else if (philo->state == DEAD)
			print_mssg(philo, "died\n");
	}
}
