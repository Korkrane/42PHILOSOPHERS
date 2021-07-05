/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 17:19:13 by bahaas            #+#    #+#             */
/*   Updated: 2021/07/05 22:11:22 by bahaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"


void *death_watcher(void *tmp)
{
	t_philo *philo;

	philo = (t_philo *)tmp;
	while(1)
	{
		//if(set_time() - philo->last_meal > set_time() - philo->last_meal + philo->main->time_to_die / 1000)
		//if(set_time() > philo->death_time)
		{
			philo->main->someone_is_dead = philo->id;
			philo->status = DIE;
		}
	}
}


void *routine(void *tmp)
{
	t_philo *philo;
	//pthread_t death;

	philo = (t_philo*)tmp;
	/*
	philo->last_meal = 0;
	philo->death_time = philo->last_meal + philo->main->time_to_die;
	if(pthread_create(&death, NULL, &death_watcher, philo) != 0)
		return ((void*)1);
	pthread_detach(death);
	*/
	//while (1 && philo->status != DIE)
	while (1)
	{
		lock_forks(philo);
		eat(philo);
		unlock_forks(philo);
		think(philo);	
	}
	return ((void *)0);
}

int launch_threads(t_main *main)
{
	void *philo;
	int i;

	i = -1;
	main->init_time = set_time();
	while(++i < main->n_philo)
	{
		philo = (void*)(&main->philos[i]);
		pthread_create(&main->philos[i].thread, NULL, &routine, philo);
		pthread_detach(main->philos[i].thread);
	//	usleep(100);
	}
	if(!main->nb_finished_eat)
	{
		while (1 && !main->someone_is_dead)
			;
	}
	else
	{
		while (main->nb_finished_eat < main->n_philo && !main->someone_is_dead)
			;
	}
//	printf("someone die : %d (last meal : %lu)\n", main->someone_is_dead, main->philos[main->someone_is_dead].last_meal);
	return (0);
}

void free_all(t_main *main)
{
	int i;

	i = -1;
	if (main->init_complete)
	{
		while (++i < main->n_philo)
		{
			if(pthread_mutex_destroy(&main->forks[i]) == EBUSY)
			{
				pthread_mutex_unlock(&main->forks[i]);
				pthread_mutex_destroy(&main->forks[i]);
			}
		}
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
	if(main.eat_limit && main.eat_limit == main.nb_finished_eat)
		printf("All of them have reached their meal limit\n");
	free_all(&main);
	return (0);
}
