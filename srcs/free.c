/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 20:20:03 by bahaas            #+#    #+#             */
/*   Updated: 2021/07/07 15:21:01 by bahaas           ###   ########.fr       */
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
	if (main->forks)
		free(main->forks);
}

int	free_mutex(t_main *main)
{
	int	i;

	pthread_mutex_unlock(&main->printer);
	pthread_mutex_destroy(&main->printer);
	pthread_mutex_unlock(&main->finished_meal);
	pthread_mutex_destroy(&main->finished_meal);
	i = -1;
	while (++i < main->nb_philo)
	{
		if (pthread_mutex_destroy(&main->forks[i]) == EBUSY)
		{
			pthread_mutex_unlock(&main->forks[i]);
			pthread_mutex_destroy(&main->forks[i]);
		}
	}
	return (FALSE);
}

void	free_all(t_main *main)
{
	free_philo(main);
	free_mutex(main);
	free_forks(main);
}
