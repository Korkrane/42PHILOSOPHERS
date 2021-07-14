/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 23:34:39 by bahaas            #+#    #+#             */
/*   Updated: 2021/07/14 16:42:57 by bahaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	lock_forks(t_philo *philo)
{
	philo->status = TAKE_FORK;
	if (philo->id % 2)
	{
		pthread_mutex_lock(philo->right_fork);
		select_mssg(philo);
		if (philo->main->nb_philo == 1)
			while (philo->status != DEAD)
				;
		else
		{
			pthread_mutex_lock(philo->left_fork);
			select_mssg(philo);
		}
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		select_mssg(philo);
		pthread_mutex_lock(philo->right_fork);
		select_mssg(philo);
	}
}

static void	eat(t_philo *philo)
{
	philo->status = EATING;
	philo->start_eat = elapsed_time(philo->main->start_time);
	select_mssg(philo);
	ft_usleep(philo->main->t_eat);
	philo->meal_taken++;
	if (philo->main->nb_meal > 0 && has_eat_enough(philo))
	{
		pthread_mutex_lock(&philo->main->finished_meal);
		philo->main->nb_finished_meal = philo->main->nb_finished_meal + 1;
		pthread_mutex_unlock(&philo->main->finished_meal);
	}
}

static void	unlock_forks(t_philo *philo)
{
	philo->status = SLEEPING;
	pthread_mutex_unlock(philo->right_fork);
	if (philo->main->nb_philo == 1)
		return ;
	pthread_mutex_unlock(philo->left_fork);
	select_mssg(philo);
	ft_usleep(philo->main->t_sleep);
}

static void	think(t_philo *philo)
{
	philo->status = THINKING;
	select_mssg(philo);
}

void	launch_cycle(t_philo *philo)
{
	lock_forks(philo);
	eat(philo);
	unlock_forks(philo);
	think(philo);
	usleep(100);
}
