/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 20:20:03 by bahaas            #+#    #+#             */
/*   Updated: 2021/07/14 16:48:39 by bahaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	free_philo(t_main *main)
{
	if (main->philo)
		free(main->philo);
}

void	free_forks(t_main *main)
{
	int	i;

	i = -1;
	while (++i < main->nb_philo)
	{
		if (pthread_mutex_destroy(&main->forks[i]) == EBUSY)
		{
			pthread_mutex_unlock(&main->forks[i]);
			pthread_mutex_destroy(&main->forks[i]);
		}
	}
	if (main->forks)
		free(main->forks);
}

void	free_mutex(t_main *main)
{
	if (pthread_mutex_destroy(&main->printer) == EBUSY)
	{
		pthread_mutex_unlock(&main->printer);
		pthread_mutex_destroy(&main->printer);
	}
	if (pthread_mutex_destroy(&main->finished_meal) == EBUSY)
	{
		pthread_mutex_unlock(&main->finished_meal);
		pthread_mutex_destroy(&main->finished_meal);
	}
	if (pthread_mutex_destroy(&main->death) == EBUSY)
	{
		pthread_mutex_unlock(&main->death);
		pthread_mutex_destroy(&main->death);
	}
}

void	free_all(t_main *main)
{
	usleep(1000000);
	free_mutex(main);
	free_forks(main);
	free_philo(main);
}
