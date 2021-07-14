/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 20:23:58 by bahaas            #+#    #+#             */
/*   Updated: 2021/07/14 16:15:22 by bahaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	init_philos(t_main *main)
{
	int	i;

	i = -1;
	main->philo = malloc(sizeof(t_philo) * main->nb_philo);
	if (!main->philo)
		return (FALSE);
	while (++i < main->nb_philo)
	{
		main->philo[i].id = i + 1;
		main->philo[i].status = THINKING;
		main->philo[i].main = main;
		main->philo[i].meal_taken = 0;
		main->philo[i].start_eat = 0;
		main->philo[i].left_fork = &main->forks[i];
		if (i == 0)
			main->philo[i].right_fork = &main->forks[main->nb_philo - 1];
		else
			main->philo[i].right_fork = &main->forks[i - 1];
	}
	return (TRUE);
}

int	init_forks(t_main *main)
{
	main->forks = malloc(sizeof(pthread_mutex_t) * main->nb_philo);
	if (!main->forks)
	{
		free_philo(main);
		return (FALSE);
	}
	return (TRUE);
}

int	init_mutex(t_main *main)
{
	int	i;

	i = -1;
	while (++i < main->nb_philo)
		pthread_mutex_init(&main->forks[i], NULL);
	pthread_mutex_init(&main->finished_meal, NULL);
	pthread_mutex_init(&main->printer, NULL);
	pthread_mutex_init(&main->death, NULL);
	return (TRUE);
}

static int	check_parameters(int ac, char **av)
{
	int	i;

	i = 0;
	while (++i < ac)
	{
		if (ft_isnumb(av[i]) == FALSE || ft_atoi(av[i]) <= 0)
			return (FALSE);
	}
	return (TRUE);
}

int	init(t_main *main, int ac, char **av)
{
	if (check_parameters(ac, av) == TRUE)
	{
		main->nb_philo = ft_atoi(av[1]);
		main->t_die = ft_atoi(av[2]);
		main->t_eat = ft_atoi(av[3]);
		main->t_sleep = ft_atoi(av[4]);
		main->nb_meal = 0;
		main->end = 0;
		if (ac == 6)
			main->nb_meal = ft_atoi(av[5]);
		main->nb_finished_meal = 0;
		main->dead_found = FALSE;
		main->philo = NULL;
		main->forks = NULL;
		if ((init_forks(main) && init_philos(main) && init_mutex(main))
			== FALSE)
			return (FALSE);
		return (TRUE);
	}
	return (FALSE);
}
