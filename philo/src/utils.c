/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghenaut- <ghenaut-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 11:06:42 by ghenaut-          #+#    #+#             */
/*   Updated: 2022/07/16 11:06:58 by ghenaut-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_atoi(const char *str)
{
	int	sign;
	int	result;
	int	i;

	result = 0;
	i = 0;
	sign = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] != '\0' && (str[i] == 43 || str[i] == 45))
	{
		if (str[i] == 45)
			sign *= -1;
		i++;
	}
	while (str[i] && str[i] >= 48 && str[i] <= 57)
	{
		result *= 10;
		result += str[i] - 48;
		i++;
	}
	result *= sign;
	return (result);
}

long long	timestamp(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

void	my_sleep(long long time, t_args *args)
{
	long long	start;
	long long	now;

	start = timestamp();
	while (!(args->someone_died))
	{
		now = timestamp();
		if (now - start >= time)
			break ;
		usleep(50);
	}
}

void	print(t_args *args, int thread_id, char *str)
{
	pthread_mutex_lock(&(args->printing));
	if (!(args->someone_died))
	{
		printf("%lli ", timestamp() - args->init_time);
		printf("%i ", thread_id + 1);
		printf("%s\n", str);
	}
	pthread_mutex_unlock(&(args->printing));
}
