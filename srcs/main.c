/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 17:19:13 by bahaas            #+#    #+#             */
/*   Updated: 2021/06/14 19:26:51 by bahaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

u_int64_t set_time(void)
{
	struct timeval time;
	gettimeofday(&time, NULL);
	return((time.tv_sec * (u_int64_t)1000) + (time.tv_usec / 1000));
}

int main(int ac, char **av)
{
	t_philo philos;
	struct timeval end;

	philos.n_philo = ft_atoi(av[0]);
	philos.init_time = set_time();
	//for(int i = 0; i < 1e5; i++)
	//{

	//}
	sleep(1);
	gettimeofday(&end, NULL);
	return 0;
}
