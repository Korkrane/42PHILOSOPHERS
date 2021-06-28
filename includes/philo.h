/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 17:19:38 by bahaas            #+#    #+#             */
/*   Updated: 2021/06/28 18:06:52 by bahaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>
#include "../libft/libft.h"

#define FALSE 0
#define TRUE 1

typedef struct s_philo
{
	int id;
	int n_eat;
	int left_fork_id;
	int right_fork_id;
	u_int64_t	last_meal;
	u_int64_t	death_time;
	struct s_main		*main;
}				t_philo;

typedef struct s_main
{
	int n_philo;
	int time_to_die;
	int time_to_eat;
	int time_to_sleep;
	int n_time_each_must_eat;
	u_int64_t init_time;

	t_philo *philos;
	pthread_mutex_t *forks;
}				t_main;


int init(t_main *main, int ac, char **av);
#endif
