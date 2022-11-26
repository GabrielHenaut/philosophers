/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghenaut- <ghenaut-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 11:05:20 by ghenaut-          #+#    #+#             */
/*   Updated: 2022/10/10 20:59:09 by ghenaut-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_mutex(t_args *args)
{
	int	i;

	i = args->nbr_of_philo;
	while (--i >= 0)
	{
		if (pthread_mutex_init(&(args->forks[i]), NULL))
			return (1);
	}
	if (pthread_mutex_init(&(args->printing), NULL))
		return (1);
	if (pthread_mutex_init(&(args->check_ate), NULL))
		return (1);
	return (0);
}

static int	init_args(int argc, char **argv, t_args *args)
{
	args->nbr_of_philo = atoi(argv[1]);
	if (args->nbr_of_philo < 1)
		return (1);
	args->time_to_die = atoi(argv[2]);
	if (args->time_to_die < 0)
		return (1);
	args->time_to_eat = atoi(argv[3]);
	if (args->time_to_eat < 0)
		return (1);
	args->time_to_sleep = atoi(argv[4]);
	if (args->time_to_sleep < 0)
		return (1);
	if (argc == 6)
	{
		args->min_eats = atoi(argv[5]);
		if (args->min_eats < 1)
			return (1);
	}
	else
		args->min_eats = -1;
	args->all_ate = 0;
	args->someone_died = 0;
	return (0);
}

static void	init_philos(t_args *args)
{
	int	i;

	i = -1;
	i = args->nbr_of_philo;
	while (--i >= 0)
	{
		args->philos[i].id = i;
		args->philos[i].times_ate = 0;
		args->philos[i].l_fork = i;
		args->philos[i].r_fork = (i + 1) % args->nbr_of_philo;
		args->philos[i].args = args;
		args->philos[i].t_since_ate = 0;
		if (args->nbr_of_philo == 1)
			args->philos[i].r_fork = -1;
	}
}

int	check_args(int argc, char **argv, t_args *args)
{
	if (argc < 5 || argc > 6)
		return (1);
	if (init_args(argc, argv, args))
		return (1);
	if (init_mutex(args))
		return (2);
	init_philos(args);
	return (0);
}
