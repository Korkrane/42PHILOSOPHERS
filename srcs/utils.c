/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 15:33:39 by bahaas            #+#    #+#             */
/*   Updated: 2021/06/29 16:40:56 by bahaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

u_int64_t set_time(void)
{
	struct timeval time;
	gettimeofday(&time, NULL);
	return((time.tv_sec * (u_int64_t)1000) + (time.tv_usec / 1000));
}

void update_timers(t_philo *philo)
{ 
	philo->last_meal = set_time();
	philo->death_time = philo->last_meal + philo->main->time_to_die;
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
