/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysanchez <ysanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 22:41:06 by ysanchez          #+#    #+#             */
/*   Updated: 2024/05/02 22:43:03 by ysanchez         ###   ########.fr       */
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

int	philo_dead(t_philo *philo)
{
	long	transcurred;
	long	time_to_die;

	transcurred = ft_gettime(philo->data->start)
		- get_value(&philo->philo_mtx, &philo->last_time_eat);
	time_to_die = philo->data->time_to_die;
	if (transcurred > time_to_die)
	{
		set_value(&philo->data->finish_mtx, &philo->data->finish, 1);
		write_status(DIED, philo);
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
