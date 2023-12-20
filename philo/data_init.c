/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysanchez <ysanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 18:25:46 by ysanchez          #+#    #+#             */
/*   Updated: 2023/12/13 18:30:28 by ysanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_forks(t_philo *philo, int pos, t_fork *forks)
{
	int	philo_num;

	philo_num = philo->args->philo_num;
	if (philo->id % 2 == 0)
	{
		philo->secondfork = &forks[pos];
		philo->firstfork = &forks[(pos + 1) % philo_num];
	}
	else
	{
		philo->firstfork = &forks[pos];
		philo->secondfork = &forks[(pos + 1) % philo_num];
	}
}

void	init_philo(t_args *args)
{
	int		i;
	t_philo	*philo;

	i = 0;
	while (i < args->philo_num)
	{
		philo = args->philoarr + i;
		philo->id = i + 1;
		philo->num_eat = 0;
		philo->goal = 0;
		philo->args = args;
		mutex_handler(&philo->philo_mutex, INIT);
		init_forks(philo, i, args->forks);
		i++;
	}
}

int	init_data(t_args *args)
{
	int	i;

	i = 0;
	args->finish = -1;
	args->ready = -1;
	args->running = 0;
	args->philoarr = malloc(sizeof(t_philo) * args->philo_num);
	if (!args->philoarr)
		return (ft_error(3));
	args->forks = malloc(sizeof(t_fork) * args->philo_num);
	if (!args->forks)
		return (ft_error(3));
	mutex_handler(&args->args_mutex, INIT);
	mutex_handler(&args->write_mutex, INIT);
	while (i < args->philo_num)
	{
		mutex_handler(&args->forks[i].fork, INIT);
		args->forks[i].id = i;
		i++;
	}
	init_philo(args);
	return (0);
}
