/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysanchez <ysanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 18:25:46 by ysanchez          #+#    #+#             */
/*   Updated: 2024/04/30 17:49:37 by ysanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_threads(t_data *data)
{
	t_philo	*philo;
	int		i;

	i = 0;
	philo = data->philoarr;
	while (i < data->philo_num)
	{
		if (thread_handler(&philo[i].thread_id, &ft_routine, &philo[i],
				CREATE) != 0)
			return (1);
		i++;
	}
	return (0);
}

void	init_forks(t_philo *philo, int pos, t_fork *forks)
{
	if (philo->id == 1)
	{
		philo->leftfork = &forks[pos];
		philo->rightfork = &forks[philo->data->philo_num - 1];
	}
	else
	{
		philo->leftfork = &forks[pos];
		philo->rightfork = &forks[(pos - 1)];
	}
}

void	init_philo(t_data *data)
{
	int		i;
	t_philo	*philo;

	i = 0;
	while (i < data->philo_num)
	{
		philo = &data->philoarr[i];
		philo->id = i + 1;
		philo->last_time_eat = 0;
		philo->num_eat = 0;
		philo->goal = 0;
		philo->data = data;
		mutex_handler(&philo->philo_mutex, INIT);
		init_forks(philo, i, data->forks);
		i++;
	}
}

static void	create_data_mtx(t_data *data)
{
	mutex_handler(&data->data_mtx, INIT);
	mutex_handler(&data->write_mtx, INIT);
	mutex_handler(&data->data_mtx, LOCK);
}

int	init_data(t_data *data)
{
	int	i;

	i = 0;
	data->finish = 0;
	data->full = 0;
	create_data_mtx(data);
	data->forks = malloc(sizeof(t_fork) * data->philo_num);
	if (!data->forks)
		return (ft_error(3));
	while (i < data->philo_num)
	{
		mutex_handler(&data->forks[i].fork_mtx, INIT);
		data->forks[i].id = i;
		i++;
	}
	data->philoarr = malloc(sizeof(t_philo) * data->philo_num);
	if (!data->philoarr)
		return (ft_error(3));
	init_philo(data);
	if (init_threads(data) != 0)
		return (1);
	return (0);
}
