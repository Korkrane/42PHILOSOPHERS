/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 17:19:13 by bahaas            #+#    #+#             */
/*   Updated: 2021/06/29 16:11:57 by bahaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void *routine(void *tmp)
{
	t_philo *philo;

	philo = (t_philo*)tmp;
	update_timers(philo);
	while (1)
	{
		lock_forks(philo);
		eat(philo);
		unlock_forks(philo);
		think(philo);	
	}
}

int launch_threads(t_main *main)
{
	void *philo;
	int i;

	print_philo_ids(main);
	i = -1;
	main->init_time = set_time();
	while(++i < main->n_philo)
	{
		philo = (void*)(&main->philos[i]);
		pthread_create(&main->philos[i].thread, NULL, &routine, philo);
		usleep(100);
	}
	i = -1;
	while(++i < main->n_philo)
		pthread_join(main->philos[i].thread, NULL);
	return (0);
}

void free_all(t_main *main)
{
	int i;

	i = -1;
	if (main->init_complete)
	{
		while (++i < main->n_philo)
			pthread_mutex_destroy(&main->forks[i]);
		free(main->forks);
		free(main->philos);
	}
}

int main(int ac, char **av)
{
	t_main main;

	if (init(&main, ac, av))
		launch_threads(&main);
	else
	{
		free_all(&main);
		ft_putstr_fd("Invalid parameters\n", 2);
		return (FALSE);
	}
	free_all(&main);
	return (0);
}
