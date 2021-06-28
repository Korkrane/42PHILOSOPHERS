/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 17:19:13 by bahaas            #+#    #+#             */
/*   Updated: 2021/06/28 19:57:09 by bahaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

u_int64_t set_time(void)
{
	struct timeval time;
	gettimeofday(&time, NULL);
	return((time.tv_sec * (u_int64_t)1000) + (time.tv_usec / 1000));
}

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

void update_timers(t_philo *philo)
{ 
	philo->last_meal = set_time();
	philo->death_time = philo->last_meal + philo->main->time_to_die;
}

void eat(t_philo *philo)
{
	philo->n_eat += 1;
	update_timers(philo);
	printf("%lums\tPhilo %d is eating\n", set_time() - philo->main->init_time, philo->id);
	usleep(philo->main->time_to_eat * 1000);
}

void think(t_philo *philo)
{
	printf("%lums\tPhilo %d is thinking\n", set_time() - philo->main->init_time, philo->id);
}

void *routine(void *philo_2)
{
	t_philo *philo;

	philo = (t_philo*)philo_2;
	update_timers(philo);
	while (1)
	{
		lock_forks(philo);
		eat(philo);
		unlock_forks(philo);
		think(philo);	
	}
	return (0);
}

void print_philo_ids(t_main *main)
{
	int i;

	i = -1;
	printf("\n");
	while(++i < main->n_philo)
	{
		printf("Philo[%d] : left_id = %d, right_id = %d\n", main->philos[i].id, main->philos[i].left_fork_id,  main->philos[i].right_fork_id);
	}
	printf("\n");
}

int launch_threads(t_main *main)
{
	pthread_t thread;
	void *philo;
	int i;

	print_philo_ids(main);
	i = -1;
	main->init_time = set_time();
	while(++i < main->n_philo)
	{
		philo = (void*)(&main->philos[i]);
		pthread_create(&thread, NULL, &routine, philo);
		pthread_detach(thread);
		//usleep(10000000);
		//sleep(1);
		usleep(1000000);
	}
	return (0);
}

void free_all(t_main *main)
{
	int i;

	i = -1;
	while (++i < main->n_philo)
		pthread_mutex_destroy(&main->forks[i]);
	free(main->forks);
	free(main->philos);
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
