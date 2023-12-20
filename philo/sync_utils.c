/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sync_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysanchez <ysanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 18:26:43 by ysanchez          #+#    #+#             */
/*   Updated: 2023/12/14 18:57:00 by ysanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	sync_threads(t_args *args)
{
	while (get_long(&args->args_mutex, &args->ready) != 0)
		;
}

long	gettime(t_time time_unit)
{
	struct timeval	time_value;

	if (gettimeofday(&time_value, NULL) != 0)
		return (ft_error(5));
	if (time_unit == SECONDS)
		return (time_value.tv_sec + (time_value.tv_usec / 1e6));
	else if (time_unit == MILLISECONDS)
		return ((time_value.tv_sec * 1e3) + (time_value.tv_usec / 1e3));
	else if (time_unit == MICROSECONDS)
		return ((time_value.tv_sec * 1e6) + time_value.tv_usec);
	else
		return (ft_error(6));
}

void	precise_usleep(long usec, t_args *args)
{
	long	start;
	long	progress;
	long	remain;

	start = gettime(MICROSECONDS);
	while (gettime(MICROSECONDS) - start < usec)
	{
		if (simulation_finished(args) == 0)
			return ;
		progress = gettime(MICROSECONDS) - start;
		remain = usec - progress;
		if (remain > 1e3)
			usleep(remain / 2);
		else
		{
			while (gettime(MICROSECONDS) - start < usec)
				;
		}
	}
}

int	check_all_running(pthread_mutex_t *mutex, long *running, long philo_num)
{
	int	flag;

	flag = 0;
	mutex_handler(mutex, LOCK);
	if (philo_num == *running)
		flag = 1;
	mutex_handler(mutex, UNLOCK);
	return (flag);
}

void	fairness_solution(t_philo *philo)
{
	if (philo->args->philo_num % 2 != 0)
	{
		if (philo->id % 2 != 0)
			ft_thinking(philo);
	}
	else
	{
		if (philo->id % 2 == 0)
			precise_usleep(30 * 1e3, philo->args);
	}
}
