/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 23:44:01 by bahaas            #+#    #+#             */
/*   Updated: 2021/07/07 15:12:40 by bahaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*routine(void *tmp)
{
	t_philo		*philo;
	pthread_t	death_control;

	philo = (t_philo *)tmp;
	pthread_create(&death_control, NULL, &control_death, philo);
	pthread_detach(death_control);
	if (philo->main->option_nb_meal)
		while (is_alive(philo) && is_hungry(philo))
			launch_cycle(philo);
	else
		while (is_alive(philo))
			launch_cycle(philo);
	return ((void *) NULL);
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
		pthread_create(&thread, NULL, &routine, (void *)philo);
		pthread_detach(thread);
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
			return (EXIT_FAILURE);
		launch_threads(&main);
		launch_monitoring(&main);
		free_all(&main);
	}
	else
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
