/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghenaut- <ghenaut-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 21:54:44 by ghenaut-          #+#    #+#             */
/*   Updated: 2022/10/10 20:56:08 by ghenaut-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdio.h>

# define ERROR_1 "Invalid args. Usage: WRITE USAGE HERE\n"
# define ERROR_1_SIZE 39
# define ERROR_2 "Error initializing mutexes.\n"
# define ERROR_2_SIZE 29
# define ERROR_3 "Error initializing threads.\n"
# define ERROR_3_SIZE 29

struct	s_args;

typedef struct s_philo
{
	int				id;
	int				r_fork;
	int				l_fork;
	int				times_ate;
	struct s_args	*args;
	pthread_t		thread;
	long long		t_since_ate;
}				t_philo;

typedef struct s_args
{
	int				nbr_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				min_eats;
	int				all_ate;
	int				someone_died;
	t_philo			philos[250];
	long long		init_time;
	pthread_mutex_t	printing;
	pthread_mutex_t	forks[250];
	pthread_mutex_t	check_ate;
}				t_args;

//philosophers.c
void		*philosophers(void *philos);

//utils.c
int			ft_atoi(const char *str);
void		print(t_args *args, int thread_id, char *str);
long long	timestamp(void);
void		my_sleep(long long time, t_args *args);

// init.c
int			check_args(int argc, char **argv, t_args *args);

// error.c
int			error(int error_code);

#endif