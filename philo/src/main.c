/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghenaut- <ghenaut-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 15:20:37 by ghenaut-          #+#    #+#             */
/*   Updated: 2022/10/10 21:51:33 by ghenaut-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	init(int argc, char **argv, t_args *args)
{
	int	error_code;

	error_code = check_args(argc, argv, args);
	if (error_code)
		return (error_code);
	return (0);
}

void	death_checker(t_args *args, t_philo *philos)
{
	int	i;

	while (!(args->all_ate))
	{
		i = -1;
		while (++i < args->nbr_of_philo && !(args->someone_died))
		{
			pthread_mutex_lock(&(args->check_ate));
			if (timestamp() - philos[i].t_since_ate > args->time_to_die)
			{
				print(args, philos[i].id, "died");
				args->someone_died = 1;
			}
			pthread_mutex_unlock(&(args->check_ate));
			usleep(100);
		}
		if (args->someone_died)
			return ;
		i = 0;
		while (args->min_eats != -1 && i < args->nbr_of_philo \
				&& philos[i].times_ate >= args->min_eats)
			i++;
		if (i == args->nbr_of_philo)
			args->all_ate = 1;
	}
}

void	exit_launcher(t_args *args, t_philo *philos)
{
	int	i;

	i = -1;
	while (++i < args->nbr_of_philo)
		pthread_join(philos[i].thread, NULL);
	i = -1;
	while (++i < args->nbr_of_philo)
		pthread_mutex_destroy(&(args->forks[i]));
	pthread_mutex_destroy(&(args->printing));
}

int	threads(t_args *args)
{
	int		i;
	t_philo	*philo;

	i = -1;
	args->init_time = timestamp();
	philo = args->philos;
	while (++i < args->nbr_of_philo)
	{
		if (pthread_create(&(philo[i].thread), NULL, \
				philosophers, (void *)&(philo[i])))
			return (1);
		philo[i].t_since_ate = timestamp();
	}
	death_checker(args, args->philos);
	exit_launcher(args, args->philos);
	return (0);
}

int	main(int argc, char **argv)
{
	t_args		args;
	int			error_code;

	error_code = init(argc, argv, &args);
	if (error_code)
		return (error(error_code));
	if (threads(&args))
		return (error(3));
	return (0);
}
