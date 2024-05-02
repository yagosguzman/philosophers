/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysanchez <ysanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 19:08:43 by ysanchez          #+#    #+#             */
/*   Updated: 2024/05/02 22:42:44 by ysanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	write_status(t_status status, t_philo *philo)
{
	long	time_passed;

	time_passed = ft_gettime(0) - philo->data->start;
	if (!simulation_finished(philo->data) || status == DIED)
	{
		mutex_handler(&philo->data->write_mtx, LOCK);
		if (status == TOOK_1ST_FORK || status == TOOK_2ND_FORK)
			printf("%ld %i has taken a fork\n", time_passed, philo->id);
		if (status == EATING)
			printf("%ld %i is eating\n", time_passed, philo->id);
		if (status == SLEEPING)
			printf("%ld %i is sleeping\n", time_passed, philo->id);
		if (status == THINKING)
			printf("%ld %i is thinking\n", time_passed, philo->id);
		if (status == DIED)
			printf("%ld %i died\n", time_passed, philo->id);
		mutex_handler(&philo->data->write_mtx, UNLOCK);
	}
}

void	solo_routine(t_philo *philo)
{
	mutex_handler(&philo->rightfork->fork_mtx, LOCK);
	write_status(TOOK_1ST_FORK, philo);
	precise_usleep(philo->data->time_to_die);
	mutex_handler(&philo->rightfork->fork_mtx, UNLOCK);
}

void	multi_routine(t_philo *philo)
{
	mutex_handler(&philo->leftfork->fork_mtx, LOCK);
	write_status(TOOK_1ST_FORK, philo);
	mutex_handler(&philo->rightfork->fork_mtx, LOCK);
	write_status(TOOK_2ND_FORK, philo);
	write_status(EATING, philo);
	set_value(&philo->philo_mtx, &philo->num_eat, (philo->num_eat + 1));
	if (philo->num_eat == philo->data->max_eat)
	{
		mutex_handler(&philo->data->data_mtx, LOCK);
		set_value(&philo->data->full_mtx,
			&philo->data->full, (philo->data->full + 1));
		mutex_handler(&philo->data->data_mtx, UNLOCK);
	}
	set_value(&philo->philo_mtx, &philo->last_time_eat,
		ft_gettime(philo->data->start));
	precise_usleep(philo->data->time_to_eat);
	mutex_handler(&philo->leftfork->fork_mtx, UNLOCK);
	mutex_handler(&philo->rightfork->fork_mtx, UNLOCK);
	write_status(SLEEPING, philo);
	precise_usleep(philo->data->time_to_sleep);
	write_status(THINKING, philo);
}
