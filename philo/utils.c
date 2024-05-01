/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysanchez <ysanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 19:16:16 by ysanchez          #+#    #+#             */
/*   Updated: 2024/04/30 21:36:13 by ysanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_gettime(long t_start)
{
	struct timeval	time_val;

	if (gettimeofday(&time_val, NULL) != 0)
		return (ft_error(4));
	return ((time_val.tv_sec * 1000) + (time_val.tv_usec / 1000) - t_start);
}

void	precise_usleep(long time)
{
	time += ft_gettime(0);
	while (ft_gettime(0) <= time)
		usleep(100);
}

int	mutex_handler(pthread_mutex_t *mutex, t_mutex operation)
{
	if (operation == INIT)
	{
		if (pthread_mutex_init(mutex, NULL) != 0)
			return (ft_mutex_error(INIT));
	}
	else if (operation == LOCK)
	{
		if (pthread_mutex_lock(mutex) != 0)
			return (ft_mutex_error(LOCK));
	}
	else if (operation == UNLOCK)
	{
		if (pthread_mutex_unlock(mutex) != 0)
			return (ft_mutex_error(UNLOCK));
	}
	else if (operation == DESTROY)
	{
		if (pthread_mutex_destroy(mutex) != 0)
			return (ft_mutex_error(DESTROY));
	}
	return (0);
}

int	thread_handler(pthread_t *thread, void *(*foo)(void *),
	void *data, t_thread operation)
{
	if (operation == CREATE)
	{
		if (pthread_create(thread, NULL, foo, data) != 0)
			return (ft_thread_error(CREATE));
	}
	else if (operation == JOIN)
	{
		if (pthread_join(*thread, NULL) != 0)
			return (ft_mutex_error(JOIN));
	}
	else if (operation == DETACH)
	{
		if (pthread_detach(*thread) != 0)
			return (ft_mutex_error(DETACH));
	}
	else
		printf("Check operation code used in thread_handler.\n");
	return (0);
}

void	clean_sim(t_data *data)
{
	t_philo	*philo;
	int		i;

	i = 0;
	while (i < data->philo_num)
		thread_handler(&data->philoarr[i++].thread_id, NULL, NULL, JOIN);
	i = 0;
	while (i < data->philo_num)
	{
		philo = &data->philoarr[i];
		mutex_handler(&data->forks[i].fork_mtx, DESTROY);
		mutex_handler(&philo->philo_mutex, DESTROY);
		i++;
	}
	mutex_handler(&data->data_mtx, DESTROY);
	mutex_handler(&data->write_mtx, DESTROY);
	if (data->forks)
		free(data->forks);
	if (data->philoarr)
		free(data->philoarr);
}
