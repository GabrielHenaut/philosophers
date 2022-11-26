/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghenaut- <ghenaut-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 20:13:38 by ghenaut-          #+#    #+#             */
/*   Updated: 2022/10/10 20:47:47 by ghenaut-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	eat(t_philo *philo, t_args *args)
{
	pthread_mutex_lock(&(args->forks[philo->l_fork]));
	print(args, philo->id, "has taken a fork");
	pthread_mutex_lock(&(args->forks[philo->r_fork]));
	print(args, philo->id, "has taken a fork");
	pthread_mutex_lock(&(args->check_ate));
	print(args, philo->id, "is eating");
	philo->t_since_ate = timestamp();
	pthread_mutex_unlock(&(args->check_ate));
	my_sleep(args->time_to_eat, args);
	(philo->times_ate)++;
	pthread_mutex_unlock(&(args->forks[philo->l_fork]));
	pthread_mutex_unlock(&(args->forks[philo->r_fork]));
}

void	*philosophers(void *philos)
{
	t_philo	*philo;
	t_args	*args;

	philo = (t_philo *)philos;
	args = philo->args;
	if (philo->id % 2)
		usleep(15000);
	while (!(args->someone_died))
	{
		eat(philo, args);
		if (args->all_ate)
			break ;
		print(args, philo->id, "is sleeping");
		my_sleep(args->time_to_sleep, args);
		print(args, philo->id, "is thinking");
	}
	return (NULL);
}
