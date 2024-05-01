/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysanchez <ysanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 13:03:44 by ysanchez          #+#    #+#             */
/*   Updated: 2024/04/30 20:25:41 by ysanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc < 5 || argc > 6)
		return (ft_error(0));
	if (checker_arg(argc, argv, &data) != 0)
		return (1);
	if (init_data(&data) != 0)
	{
		clean_sim(&data);
		return (1);
	}
	ft_checker(&data);
	clean_sim(&data);
	printf("Dining finished.\n");
	return (0);
}
