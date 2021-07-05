/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 18:56:17 by bahaas            #+#    #+#             */
/*   Updated: 2021/07/05 21:50:37 by bahaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"


void    print_mssg(t_philo *philo, char *status)
{
	char *time;
	char *id;
	char *mssg;

	time = ft_itoa(set_time() - philo->main->init_time);
	id = ft_itoa(philo->id);
	mssg = ft_strjoin(time, "ms\tPhilo ");
	mssg = ft_strjoin(mssg, id);
	mssg = ft_strjoin(mssg, " ");
	mssg = ft_strjoin(mssg, status);
    pthread_mutex_lock(philo->main->printer);
	ft_putstr_fd(mssg,1);
    pthread_mutex_unlock(philo->main->printer);
}

void select_mssg(t_philo *philo)
{
    if(philo->status == TAKE_FORK)
        print_mssg(philo, "has taken a fork\n");
    else if(philo->status == EAT)
        print_mssg(philo, "is eating\n");
    else if(philo->status == SLEEP)
        print_mssg(philo, "is sleeping\n");
    else if(philo->status == THINK)
        print_mssg(philo, "is thinking\n");
    else if(philo->status == DIE)
        print_mssg(philo, "died\n");
}
