/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_set_mutex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysanchez <ysanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 16:32:20 by ysanchez          #+#    #+#             */
/*   Updated: 2024/05/02 21:35:51 by ysanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_value(pthread_mutex_t *mutex, long *dst, long value)
{
	mutex_handler(mutex, LOCK);
	*dst = value;
	mutex_handler(mutex, UNLOCK);
}

long	get_value(pthread_mutex_t *mutex, long *src)
{
	long	result;

	mutex_handler(mutex, LOCK);
	result = *src;
	mutex_handler(mutex, UNLOCK);
	return (result);
}

int	all_philos_full(t_data *data)
{
	long	philos_full;

	philos_full = get_value(&data->full_mtx, &data->full);
	if (philos_full == data->philo_num)
	{
		set_value(&data->finish_mtx, &data->finish, 1);
		return (1);
	}
	return (0);
}

int	simulation_finished(t_data *data)
{
	if (get_value(&data->finish_mtx, &data->finish) == 1)
		return (1);
	return (0);
}
