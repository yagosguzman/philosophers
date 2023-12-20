/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysanchez <ysanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 14:52:29 by ysanchez          #+#    #+#             */
/*   Updated: 2023/12/20 17:47:33 by ysanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	is_space(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (0);
	else
		return (1);
}

static int	check_valid_arg(char **argv)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (argv[i])
	{
		while (is_space(argv[i][j]) == 0)
			j++;
		if (argv[i][j] == '\0')
			return (1);
		if (argv[i][j] == '+')
			j++;
		while (argv[i][j] != '\0')
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (1);
			else
				j++;
		}
		i++;
		j = 0;
	}
	return (0);
}
// DUDA SI GUARDAR EL TIMETOX EN MILI O MICRO
static void	save_info(int i, long result, t_args *args)
{
	if (i == 1)
		args->philo_num = result;
	if (i == 2)
		args->time_to_die = result * 1000;
	if (i == 3)
		args->time_to_eat = result * 1000;
	if (i == 4)
		args->time_to_sleep = result * 1000;
	if (i == 5)
		args->max_eat = result;
}

static long	arg_to_long(int argnum, char *str, t_args *args)
{
	int		i;
	long	result;

	i = 0;
	result = 0;
	while (is_space(str[i]) == 0 && str[i] != '\0')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = (result * 10) + (str[i] - 48);
		i++;
	}
	if (result > LONG_MAX)
		return (-1);
	else
		save_info(argnum, result, args);
	return (0);
}

int	checker_philo(int argc, char **argv, t_args *args)
{
	int	i;

	i = 1;
	if (argc == 5)
		args->max_eat = -1;
	if (check_valid_arg(argv) == 1)
		return (ft_error(1));
	while (i < argc)
	{
		if (arg_to_long(i, argv[i], args) == -1)
			return (ft_error(2));
		i++;
	}
	return (0);
}
