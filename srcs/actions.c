/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 23:34:39 by bahaas            #+#    #+#             */
/*   Updated: 2021/07/07 18:37:25 by bahaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	lock_forks(t_philo *philo)
{
	philo->state = TAKE_FORK;
	if (philo->num % 2)
	{
		pthread_mutex_lock(philo->right_fork);
		select_mssg(philo);
		pthread_mutex_lock(philo->left_fork);
		select_mssg(philo);
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
	philo->state = EATING;
	philo->meal_taken++;
	philo->start_eat = elapsed_time(philo->main->start_time);
	select_mssg(philo);
	usleep(philo->main->t_eat * 1000);
	if (philo->main->nb_meal > 0 && has_eat_enough(philo))
	{
		pthread_mutex_lock(&philo->main->finished_meal);
		philo->main->nb_finished_meal = philo->main->nb_finished_meal + 1;
		pthread_mutex_unlock(&philo->main->finished_meal);
	}
}

static void	unlock_forks(t_philo *philo)
{
	philo->state = SLEEPING;
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	select_mssg(philo);
	usleep(philo->main->t_sleep * 1000);
}

static void	think(t_philo *philo)
{
	philo->state = THINKING;
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
