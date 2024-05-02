/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dining.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysanchez <ysanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 20:58:46 by ysanchez          #+#    #+#             */
/*   Updated: 2024/05/02 15:59:03 by ysanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	solo_philo(t_philo *philo)
{
	mutex_handler(&philo->rightfork->fork_mtx, LOCK);
	write_status(TOOK_1ST_FORK, philo);
	precise_usleep(philo->data->time_to_die);
	write_status(DIED, philo);
	mutex_handler(&philo->rightfork->fork_mtx, UNLOCK);
	set_value(&philo->data->finish_mtx, &philo->data->finish, 1);
}

void	*ft_routine(void *v_data)
{
	t_philo	*philo;

	philo = (t_philo *)v_data;
	mutex_handler(&philo->data->data_mtx, LOCK);
	mutex_handler(&philo->data->data_mtx, UNLOCK);
	if (philo->data->philo_num > 1 && philo->id % 2 != 0)
		precise_usleep(philo->data->time_to_eat / 10);
	while (!simulation_finished(philo->data))
	{
		if (philo->data->philo_num == 1)
			solo_philo(philo);
		else
		{
			ft_eating(philo);
			ft_sleeping(philo);
			ft_thinking(philo);
		}
	}
	return (NULL);
}

int	philo_dead(t_philo *philo)
{
	long	transcurred;
	long	time_to_die;

	transcurred = ft_gettime(philo->data->start)
		- get_value(&philo->philo_mtx, &philo->last_time_eat);
	time_to_die = philo->data->time_to_die;
	if (transcurred > time_to_die)
		return (1);
	return (0);
}

void	ft_checker(t_data *data)
{
	int	i;

	i = 0;
	data->start = ft_gettime(0);
	mutex_handler(&data->data_mtx, UNLOCK);
	while (!simulation_finished(data))
	{
		while (i < data->philo_num && !simulation_finished(data))
		{
			if (philo_dead(&data->philoarr[i]))
			{
				write_status(DIED, &data->philoarr[i]);
				set_value(&data->finish_mtx, &data->finish, 1);
			}
			if (get_value(&data->philoarr[i].philo_mtx,
					&data->philoarr[i].goal) == 1)
			{
				set_value(&data->philoarr[i].philo_mtx,
					&data->philoarr[i].goal, 2);
				set_value(&data->finish_mtx, &data->finish, (data->finish + 1));
			}
			i++;
			if (i == data->philo_num)
				i = 0;
		}
	}
}
