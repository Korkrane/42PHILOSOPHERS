/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 23:44:01 by bahaas            #+#    #+#             */
/*   Updated: 2021/07/14 16:51:25 by bahaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*routine(void *tmp)
{
	t_philo		*philo;
	pthread_t	death;

	philo = (t_philo *)tmp;
	pthread_create(&death, NULL, &death_watch, philo);
	pthread_detach(death);
	if (philo->main->nb_meal > 0)
		while (is_alive(philo) && is_hungry(philo))
			launch_cycle(philo);
	else
		while (is_alive(philo))
			launch_cycle(philo);
	return ((void *) 0);
}

void	launch_threads(t_main *main)
{
	pthread_t	thread;
	t_philo		*philo;
	int			i;

	main->start_time = get_time();
	i = -1;
	while (++i < main->nb_philo)
	{
		philo = &main->philo[i];
		if (pthread_create(&thread, NULL, &routine, (void *)philo) != 0)
			return (free_all(main));
		pthread_detach(thread);
		usleep(100);
	}
}

void	launch_monitoring(t_main *main)
{
	if (main->nb_meal > 0)
		meal_and_death_monitor(main);
	else
		death_monitor(main);
}

int	main(int ac, char **av)
{
	t_main	main;

	if (ac >= 5 && ac <= 6)
	{
		if (!init(&main, ac, av))
		{
			printf("Invalid parameters\n");
			return (1);
		}
		launch_threads(&main);
		launch_monitoring(&main);
		free_all(&main);
	}
	else
	{
		printf("Invalid number of parameters\n");
		return (1);
	}
	return (0);
}
