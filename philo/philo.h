/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysanchez <ysanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 13:29:49 by ysanchez          #+#    #+#             */
/*   Updated: 2024/05/02 22:44:52 by ysanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>

typedef enum e_thread
{
	CREATE,
	JOIN,
	DETACH
}	t_thread;

typedef enum e_mutex
{
	INIT,
	LOCK,
	UNLOCK,
	DESTROY
}	t_mutex;

typedef enum e_status
{
	EATING,
	SLEEPING,
	THINKING,
	TOOK_1ST_FORK,
	TOOK_2ND_FORK,
	DIED
}	t_status;

typedef struct s_data	t_data;

typedef struct s_fork
{
	pthread_mutex_t	fork_mtx;
	int				id;
}	t_fork;

typedef struct s_philo
{
	pthread_t		thread_id;
	int				id;
	long			num_eat;
	long			last_time_eat;
	t_data			*data;
	pthread_mutex_t	philo_mtx;
	t_fork			*leftfork;
	t_fork			*rightfork;
}	t_philo;

struct s_data
{
	long			philo_num;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			max_eat;
	long			finish;
	long			full;
	long			start;
	pthread_mutex_t	data_mtx;
	pthread_mutex_t	write_mtx;
	pthread_mutex_t	finish_mtx;
	pthread_mutex_t	full_mtx;
	t_fork			*forks;
	t_philo			*philoarr;
} ;

/*########## parser.c ##########*/
void	save_info(int i, long result, t_data *data);
int		ft_atol(int argnum, char *str, t_data *data);
int		check_valid_arg(char **argv);
int		checker_arg(int argc, char **argv, t_data *data);

/*########## data_init.c ##########*/
int		init_threads(t_data *data);
void	init_forks(t_philo *philo, int pos, t_fork *forks);
void	init_philo(t_data *data);
int		init_data(t_data *data);

/*########## error_handler.c ##########*/
int		ft_error(int errnum);
int		ft_mutex_error(int errnum);
int		ft_thread_error(int errnum);

/*########## checkers.c ##########*/
void	set_value(pthread_mutex_t *mutex, long *dst, long value);
long	get_value(pthread_mutex_t *mutex, long *src);
int		all_philos_full(t_data *data);
int		philo_dead(t_philo *philo);
int		simulation_finished(t_data *data);

/*########## instructions.c ##########*/
void	write_status(t_status status, t_philo *philo);
void	solo_routine(t_philo *philo);
void	multi_routine(t_philo *philo);

/*########## utils.c ##########*/
long	ft_gettime(long t_start);
void	precise_usleep(long time);
int		mutex_handler(pthread_mutex_t *mutex, t_mutex operation);
int		thread_handler(pthread_t *thread, void *(*foo)(void *),
			void *data, t_thread operation);
void	clean_sim(t_data *data);

/*########## dining.c ##########*/
void	*ft_routine(void *v_data);
void	ft_checker(t_data *data);

#endif
