/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysanchez <ysanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 19:16:16 by ysanchez          #+#    #+#             */
/*   Updated: 2023/12/13 18:27:39 by ysanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	else
		printf("Check the operation code used mutex_handler.\n");
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
		printf("Check the operation code used in thread_handler.\n");
	return (0);
}

void	clean_sim(t_args *args)
{
	t_philo	*philo;
	int		i;

	i = 0;
	while (i < args->philo_num)
	{
		philo = args->philoarr + i;
		mutex_handler(&philo->philo_mutex, DESTROY);
		i++;
	}
	mutex_handler(&args->args_mutex, DESTROY);
	mutex_handler(&args->write_mutex, DESTROY);
	free(args->forks);
	free(args->philoarr);
	printf("Dining finshed.\n");
}
