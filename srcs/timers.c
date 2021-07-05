/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timers.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 16:21:55 by bahaas            #+#    #+#             */
/*   Updated: 2021/07/05 22:12:52 by bahaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int		death_time_checker(t_main *main)
{
	int i;
	u_int64_t last_meal_time;

	i = -1;
	while (++i < main->n_philo)
	{
		last_meal_time = set_time() - main->philos[i].last_meal;
		if (last_meal_time >= main->time_to_die)
		{
			printf("%lums last meal lol \n", last_meal_time);
			printf("%lums last meal of philo %d lol \n", main->philos[i].last_meal, i);
			return (1);
		}
	}
	return (0);
}
