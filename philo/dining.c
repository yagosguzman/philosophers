/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dining.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysanchez <ysanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 20:58:46 by ysanchez          #+#    #+#             */
/*   Updated: 2024/05/02 22:19:54 by ysanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
		{
			solo_routine(philo);
			break ;
		}
		else
			multi_routine(philo);
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
	{
		set_value(&philo->data->finish_mtx, &philo->data->finish, 1);
		write_status(DIED, philo);
		return (1);
	}
	return (0);
}

void	ft_checker(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_num)
	{
		if (philo_dead(&data->philoarr[i]))
			break ;
		if (data->max_eat != -1 && all_philos_full(data))
			break ;
		i++;
		if (i == data->philo_num)
			i = 0;
	}
}
