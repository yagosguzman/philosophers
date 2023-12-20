/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysanchez <ysanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 19:08:43 by ysanchez          #+#    #+#             */
/*   Updated: 2023/12/14 18:52:01 by ysanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	write_status(t_status status, t_philo *philo)
{
	long	time_passed;

	time_passed = gettime(MILLISECONDS) - philo->args->start;
	if (get_long(&philo->args->args_mutex, &philo->goal))
		return ;
	mutex_handler(&philo->args->write_mutex, LOCK);
	if (simulation_finished(philo->args) != 0)
	{
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
	}
	mutex_handler(&philo->args->write_mutex, UNLOCK);
}

void	ft_eating(t_philo *philo)
{
	if (philo->goal == 1)
		return ;
	else
	{
		mutex_handler(&philo->firstfork->fork, LOCK);
		write_status(TOOK_1ST_FORK, philo);
		mutex_handler(&philo->secondfork->fork, LOCK);
		write_status(TOOK_2ND_FORK, philo);
		set_long(&philo->philo_mutex, &philo->last_time_eat,
			gettime(MILLISECONDS));
		set_long(&philo->philo_mutex, &philo->num_eat,
			philo->num_eat + 1);
		write_status(EATING, philo);
		precise_usleep(philo->args->time_to_sleep, philo->args);
		if (philo->num_eat == philo->args->max_eat)
			set_long(&philo->philo_mutex, &philo->goal, 1);
		mutex_handler(&philo->firstfork->fork, UNLOCK);
		mutex_handler(&philo->secondfork->fork, UNLOCK);
	}
}

void	ft_sleeping(t_philo *philo)
{
	write_status(SLEEPING, philo);
	precise_usleep(philo->args->time_to_sleep, philo->args);
}

void	ft_thinking(t_philo *philo)
{
	long	time_to_eat;
	long	time_to_sleep;
	long	time_to_think;

	write_status(THINKING, philo);
	if (philo->args->philo_num % 2 == 0)
		return ;
	else
	{
		time_to_eat = philo->args->time_to_eat;
		time_to_sleep = philo->args->time_to_sleep;
		time_to_think = (time_to_eat * 2) - time_to_sleep;
		if (time_to_think < 0)
			time_to_think = 0;
		precise_usleep((time_to_think / 2), philo->args);
	}
}
