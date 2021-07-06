/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 23:33:33 by bahaas            #+#    #+#             */
/*   Updated: 2021/07/06 23:33:37 by bahaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

long  elapsed_time(long starter)
{
	struct timeval  tv;
	long            end;

	gettimeofday(&tv, NULL);
	end = ((tv.tv_sec * 1000) + tv.tv_usec / 1000);
	return (end - starter);
}

long  get_time()
{
	struct timeval  tv;
	long            end;

	gettimeofday(&tv, NULL);
	end = ((tv.tv_sec * 1000) + tv.tv_usec / 1000);
	return (end); 
}

void  ft_usleep(int duration)
{
	long start;
	long current;

	start = elapsed_time(0);
	current = start;
	while (duration > current - start)
	{
		usleep(100);
		current = elapsed_time(0);
	}
}
