/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysanchez <ysanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 14:52:29 by ysanchez          #+#    #+#             */
/*   Updated: 2024/04/25 18:15:19 by ysanchez         ###   ########.fr       */
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

void	save_info(int i, long result, t_data *data)
{
	if (i == 1)
		data->philo_num = result;
	else if (i == 2)
		data->time_to_die = result;
	else if (i == 3)
		data->time_to_eat = result;
	else if (i == 4)
		data->time_to_sleep = result;
	else if (i == 5)
		data->max_eat = result;
	else
		return ;
}

int	ft_atol(int argnum, char *str, t_data *data)
{
	int		i;
	int		j;
	long	result;

	i = 0;
	result = 0;
	while (str[i] != '\0' && is_space(str[i]) == 0)
		i++;
	if (str[i] == '+')
		i++;
	j = i;
	while (str[j])
		j++;
	if ((j - i) > 19)
		return (1);
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = (result * 10) + (str[i] - 48);
		i++;
	}
	if (result > LONG_MAX || result <= 0)
		return (1);
	else
		save_info(argnum, result, data);
	return (0);
}

int	check_valid_arg(char **argv)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (argv[i])
	{
		while (is_space(argv[i][j]) == 0)
			j++;
		if (argv[i][j] == '\0' || (argv[i][j] == '+' && argv[i][j + 1] == '\0'))
			return (1);
		if (argv[i][j] == '+')
			j++;
		while (argv[i][j])
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

int	checker_arg(int argc, char **argv, t_data *data)
{
	int	i;

	i = 1;
	if (argc == 5)
		data->max_eat = -1;
	if (check_valid_arg(argv) == 1)
		return (ft_error(1));
	while (i < argc)
	{
		if (ft_atol(i, argv[i], data) == 1)
			return (ft_error(2));
		i++;
	}
	return (0);
}
