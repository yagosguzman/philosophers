/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysanchez <ysanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 19:08:43 by ysanchez          #+#    #+#             */
/*   Updated: 2024/05/02 15:46:27 by ysanchez         ###   ########.fr       */
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
		if (status == TOOK_1ST_FORK || status == TOOK_2ND_FORK)
			printf("%ld %i has taken a fork\n", time_passed, philo->id);
		if (status == EATING)
		{
			printf("%ld %i is eating\n", time_passed, philo->id);
			printf("Philo %i has eaten %ld times\n", philo->id, philo->num_eat);
		}
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
	mutex_handler(&philo->philo_mtx, LOCK);
	mutex_handler(&philo->leftfork->fork_mtx, LOCK);
	write_status(TOOK_1ST_FORK, philo);
	mutex_handler(&philo->rightfork->fork_mtx, LOCK);
	write_status(TOOK_2ND_FORK, philo);
	write_status(EATING, philo);
	philo->last_time_eat = ft_gettime(philo->data->start);
	philo->num_eat++;
	if (philo->num_eat == philo->data->max_eat)
		philo->goal = 1;
	precise_usleep(philo->data->time_to_eat);
	mutex_handler(&philo->leftfork->fork_mtx, UNLOCK);
	mutex_handler(&philo->rightfork->fork_mtx, UNLOCK);
	mutex_handler(&philo->philo_mtx, UNLOCK);
}

void	ft_sleeping(t_philo *philo)
{
	write_status(SLEEPING, philo);
	precise_usleep(philo->data->time_to_sleep);
}

void	ft_thinking(t_philo *philo)
{
	write_status(THINKING, philo);
}
