/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 23:45:25 by bahaas            #+#    #+#             */
/*   Updated: 2021/07/14 16:48:20 by bahaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <errno.h>

# define FALSE 0
# define TRUE 1

typedef enum e_status
{
	THINKING,
	DEAD,
	TAKE_FORK,
	EATING,
	SLEEPING
}				t_status;

typedef struct s_philo
{
	int				id;
	int				status;
	int				meal_taken;
	long			start_eat;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	struct s_main	*main;
}				t_philo;

typedef struct s_main
{
	int				nb_philo;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				nb_meal;
	int				nb_finished_meal;
	int				dead_found;
	long			start_time;
	t_philo			*philo;
	pthread_mutex_t	*forks;
	pthread_mutex_t	printer;
	pthread_mutex_t	finished_meal;
	pthread_mutex_t	death;
	int				end;
}				t_main;

int		init(t_main *main, int ac, char **av);

void	select_mssg(t_philo *philo);

void	*routine(void *data);
void	launch_cycle(t_philo *philo);
void	*death_watch(void *tmp);
void	death_monitor(t_main *main);
void	meal_and_death_monitor(t_main *main);

void	free_all(t_main *main);
void	free_mutex(t_main *main);
void	free_forks(t_main *main);
void	free_philo(t_main *main);

void	ft_usleep(int time);
int		ft_atoi(const char *str);
int		ft_isnumb(char *num);
char	*ft_itoa(long n);

long	elapsed_time(long starter);
long	get_time(void);
int		is_alive(t_philo *philo);
int		is_hungry(t_philo *philo);
int		has_eat_enough(t_philo *philo);
#endif
