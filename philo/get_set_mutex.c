/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_set_mutex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysanchez <ysanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 16:32:20 by ysanchez          #+#    #+#             */
/*   Updated: 2023/12/20 14:52:55 by ysanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_long(pthread_mutex_t *mutex, long *dst, long value)
{
	mutex_handler(mutex, LOCK);
	*dst = value;
	mutex_handler(mutex, UNLOCK);
}

long	get_long(pthread_mutex_t *mutex, long *src)
{
	long	result;

	mutex_handler(mutex, LOCK);
	result = *src;
	mutex_handler(mutex, UNLOCK);
	return (result);
}

int	simulation_finished(t_args *args)
{
	return (get_long(&args->args_mutex, &args->finish));
}
