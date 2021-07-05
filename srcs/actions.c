/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 15:29:23 by bahaas            #+#    #+#             */
/*   Updated: 2021/07/05 22:14:22 by bahaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void lock_forks(t_philo *philo)
{
	if(philo->left_fork_id < philo->right_fork_id)
	{
		philo->status = TAKE_FORK;
		pthread_mutex_lock(&philo->main->forks[philo->left_fork_id]);
		select_mssg(philo);
		pthread_mutex_lock(&philo->main->forks[philo->right_fork_id]);
		select_mssg(philo);
	} 
	else if(philo->left_fork_id > philo->right_fork_id) 
	{
		philo->status = TAKE_FORK;
		pthread_mutex_lock(&philo->main->forks[philo->right_fork_id]);
		select_mssg(philo);
		pthread_mutex_lock(&philo->main->forks[philo->left_fork_id]);
		select_mssg(philo);
	}
	else //If there is only one philo
	{
		philo->status = TAKE_FORK;
		pthread_mutex_lock(&philo->main->forks[philo->right_fork_id]);
		select_mssg(philo);
		pthread_mutex_lock(&philo->main->forks[philo->right_fork_id]);
		select_mssg(philo);
	}
}

void unlock_forks(t_philo *philo)
{
	philo->status = SLEEP;
	pthread_mutex_unlock(&philo->main->forks[philo->left_fork_id]);
	pthread_mutex_unlock(&philo->main->forks[philo->right_fork_id]);
	select_mssg(philo);
	usleep(philo->main->time_to_sleep * 1000); 
}


void eat(t_philo *philo)
{
	philo->status = EAT;
	u_int64_t local_time = set_time();
	philo->last_meal = local_time - philo->main->init_time;
	philo->meal_taken += 1;
	if(philo->meal_taken == philo->main->eat_limit)
		philo->main->nb_finished_eat += 1;
	update_timers(philo);
	select_mssg(philo);
	usleep(philo->main->time_to_eat * 1000);
	local_time = set_time();
	//printf("%lums, last meal for philo %d was %lums ago\n", local_time - philo->main->init_time, philo->id, local_time - philo->last_meal);
}

void think(t_philo *philo)
{
	philo->status = THINK;
	select_mssg(philo);
}
