/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 17:47:27 by bahaas            #+#    #+#             */
/*   Updated: 2021/06/28 19:31:24 by bahaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int check_parameters(int ac, char **av)
{
	int i;

	i = 1;
	while(i < ac - 1)
	{
		if (ft_isnumb(av[i]) == FALSE)
			return (FALSE);
		i++;
	}
	return (TRUE);
}

static int init_forks(t_main *main)
{
	int i;

	main->forks = malloc(sizeof(pthread_mutex_t) * main->n_philo);
	if(!main->forks)
		return (FALSE);
	i = -1;
	while (++i < main->n_philo)
		pthread_mutex_init(&main->forks[i], NULL);
	return (TRUE);
}

static int init_philos(t_main *main)
{
	int i;

	main->philos = malloc(sizeof(t_philo) * main->n_philo);
	if(!main->philos)
		return (FALSE);
	i = -1;
	while (++i < main->n_philo)
	{
		main->philos[i].id = i;
		main->philos[i].n_eat = 0;
		if (i == 0)
		main->philos[i].left_fork_id = main->n_philo - 1;
		else
		main->philos[i].left_fork_id = main->philos[i].id - 1;
		main->philos[i].right_fork_id = (main->philos[i].left_fork_id + 1) % main->n_philo;
		main->philos[i].last_meal = 0;
		main->philos[i].death_time = 0;
		main->philos[i].main = main;
	}
	return (TRUE);
}

int init(t_main *main, int ac, char **av)
{
	if (check_parameters(ac, av) == TRUE && (ac == 5 || ac == 6))
	{
		main->n_philo = ft_atoi(av[1]);
		main->time_to_die = ft_atoi(av[2]);
		main->time_to_eat = ft_atoi(av[3]);
		main->time_to_sleep = ft_atoi(av[4]);
		if (ac == 6)
			main->n_time_each_must_eat = ft_atoi(av[5]);
		else
			main->n_time_each_must_eat = 0;
		if(init_philos(main) == FALSE || init_forks(main) == FALSE)
			return (FALSE);
		printf("Init [OK]\n");
		printf("\tTotal philo : %d\n", main->n_philo);
		printf("\ttime_to_die : %d\n", main->time_to_die);
		printf("\ttime_to_eat : %d\n", main->time_to_eat);
		printf("\ttime_to_sleep : %d\n", main->time_to_sleep);
		if (ac == 6)
			printf("\tn_time_each_must_eat : %d\n", main->n_time_each_must_eat);
		return (TRUE);
	}
	return (FALSE);
}
