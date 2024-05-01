/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysanchez <ysanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 19:08:43 by ysanchez          #+#    #+#             */
/*   Updated: 2024/04/30 21:35:54 by ysanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	write_status(t_status status, t_philo *philo)
{
	long	time_passed;

	time_passed = ft_gettime(0) - philo->data->start;
	mutex_handler(&philo->data->write_mtx, LOCK);
	if (!simulation_finished(philo->data))
	{
		if (status == TOOK_1ST_FORK)
			printf("%ld %i has taken left fork\n", time_passed, philo->id);
		if (status == TOOK_2ND_FORK)
			printf("%ld %i has taken right fork\n", time_passed, philo->id);
		if (status == EATING)
			printf("%ld %i is eating\n", time_passed, philo->id);
		if (status == SLEEPING)
			printf("%ld %i is sleeping\n", time_passed, philo->id);
		if (status == THINKING)
			printf("%ld %i is thinking\n", time_passed, philo->id);
		if (status == DIED)
			printf("%ld %i died\n", time_passed, philo->id);
	}
	mutex_handler(&philo->data->write_mtx, UNLOCK);
}

void	ft_eating(t_philo *philo)
{
	mutex_handler(&philo->leftfork->fork_mtx, LOCK);
	write_status(TOOK_1ST_FORK, philo);
	mutex_handler(&philo->rightfork->fork_mtx, LOCK);
	write_status(TOOK_2ND_FORK, philo);
	set_value(&philo->philo_mutex, &philo->last_time_eat,
		ft_gettime(philo->data->start));
	set_value(&philo->philo_mutex, &philo->num_eat,
		philo->num_eat + 1);
	if (philo->num_eat == philo->data->max_eat)
		set_value(&philo->data->data_mtx, &philo->data->full,
			philo->data->full + 1);
	write_status(EATING, philo);
	precise_usleep(philo->data->time_to_eat);
	mutex_handler(&philo->leftfork->fork_mtx, UNLOCK);
	mutex_handler(&philo->rightfork->fork_mtx, UNLOCK);
}

void	ft_sleeping(t_philo *philo)
{
	write_status(SLEEPING, philo);
	precise_usleep(philo->data->time_to_sleep);
}

void	ft_thinking(t_philo *philo)
{
	long	time_to_eat;
	long	time_to_sleep;
	long	time_to_think;

	write_status(THINKING, philo);
	if (philo->data->philo_num % 2 == 0)
		return ;
	else
	{
		time_to_eat = philo->data->time_to_eat;
		time_to_sleep = philo->data->time_to_sleep ;
		time_to_think = (time_to_eat * 2) - time_to_sleep;
		if (time_to_think < 0)
			time_to_think = 0;
		precise_usleep((time_to_think / 2));
	}
}
