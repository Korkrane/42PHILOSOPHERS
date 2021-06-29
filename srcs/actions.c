/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 15:29:23 by bahaas            #+#    #+#             */
/*   Updated: 2021/06/29 18:12:35 by bahaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void lock_forks(t_philo *philo)
{
	if(philo->left_fork_id < philo->right_fork_id)
	{
		pthread_mutex_lock(&philo->main->forks[philo->left_fork_id]);
		printf("%lums\tPhilo %d has taken his left fork[%d]\n",set_time() - philo->main->init_time, philo->id, philo->left_fork_id);
		pthread_mutex_lock(&philo->main->forks[philo->right_fork_id]);
		printf("%lums\tPhilo %d has taken his right fork[%d]\n",set_time() - philo->main->init_time, philo->id, philo->right_fork_id);
	} 
	else 
	{
		pthread_mutex_lock(&philo->main->forks[philo->right_fork_id]);
		printf("%lums\tPhilo %d has taken his right fork[%d]\n",set_time() - philo->main->init_time, philo->id, philo->right_fork_id);
		pthread_mutex_lock(&philo->main->forks[philo->left_fork_id]);
		printf("%lums\tPhilo %d has taken his left fork[%d]\n",set_time() - philo->main->init_time, philo->id, philo->left_fork_id);
	}
}

void unlock_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->main->forks[philo->left_fork_id]);
	pthread_mutex_unlock(&philo->main->forks[philo->right_fork_id]);
	printf("%lums\tPhilo %d is sleeping\n", set_time() - philo->main->init_time, philo->id);
	usleep(philo->main->time_to_sleep * 1000); 
}


void eat(t_philo *philo)
{
	philo->last_meal = set_time() - philo->main->init_time;
	philo->n_eat += 1;
	update_timers(philo);
	printf("%lums\tPhilo %d is eating (n_eat:%d)\n", set_time() - philo->main->init_time, philo->id, philo->n_eat);
	usleep(philo->main->time_to_eat * 1000);
}

void think(t_philo *philo)
{
	printf("%lums\tPhilo %d is thinking\n", set_time() - philo->main->init_time, philo->id);
}
