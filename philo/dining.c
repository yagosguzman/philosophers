/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dining.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysanchez <ysanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 20:58:46 by ysanchez          #+#    #+#             */
/*   Updated: 2024/05/02 22:42:37 by ysanchez         ###   ########.fr       */
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
