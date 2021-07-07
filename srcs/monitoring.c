/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 23:38:23 by bahaas            #+#    #+#             */
/*   Updated: 2021/07/07 18:53:48 by bahaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	death_monitor(t_main *main)
{
	while (!main->dead_found)
		usleep(100);
}

void	meal_and_death_monitor(t_main *main)
{
	while (!main->dead_found
		&& main->nb_finished_meal < main->nb_philo)
		usleep(100);
	if (main->nb_finished_meal == main->nb_philo && !main->dead_found)
		printf("\nEach philosopher have eat %d times.\n", main->nb_meal);
}

static int	is_dead(t_philo *philo)
{
	long	time;

	time = elapsed_time(philo->main->start_time);
	if ((philo->main->t_die < time - philo->start_eat)
		&& philo->state != EATING)
	{
		philo->state = DEAD;
		select_mssg(philo);
		philo->main->dead_found = TRUE;
		return (1);
	}
	usleep(100);
	return (0);
}

void	*control_death(void *tmp)
{
	t_philo	*philo;

	philo = (t_philo *)tmp;
	if (philo->main->nb_meal > 0)
	{
		while (is_alive(philo) && is_hungry(philo))
			if (is_dead(philo))
				break ;
	}
	else
	{
		while (is_alive(philo))
			if (is_dead(philo))
				break ;
	}
	return (NULL);
}
