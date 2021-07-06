/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 21:45:01 by bahaas            #+#    #+#             */
/*   Updated: 2021/07/06 21:46:33 by bahaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_isnumb(char *num)
{
	int	i;

	i = 0;
	if (num[i] != '\0')
	{
		while (num[i])
		{
			if (num[i] == '+' || num[i] == '-')
				i++;
			else
				break ;
		}
		while (num[i])
		{
			if (ft_isdigit(num[i]))
				i++;
			else
				return (0);
		}
		return (1);
	}
	return (0);
}
