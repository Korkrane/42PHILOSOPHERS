/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 23:44:27 by bahaas            #+#    #+#             */
/*   Updated: 2021/07/07 15:27:34 by bahaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

long	elapsed_time(long starter)
{
	struct timeval	tv;
	long			end;

	gettimeofday(&tv, NULL);
	end = ((tv.tv_sec * 1000) + tv.tv_usec / 1000);
	return (end - starter);
}

long	get_time(void)
{
	struct timeval	tv;
	long			end;

	gettimeofday(&tv, NULL);
	end = ((tv.tv_sec * 1000) + tv.tv_usec / 1000);
	return (end);
}

int	is_alive(t_philo *philo)
{
	if (philo->status != DEAD && !philo->main->dead_found)
		return (1);
	return (0);
}

int	is_hungry(t_philo *philo)
{
	if (philo->meal_taken < philo->main->nb_meal)
		return (1);
	return (0);
}

int	has_eat_enough(t_philo *philo)
{
	if (philo->meal_taken == philo->main->nb_meal)
		return (1);
	return (0);
}
