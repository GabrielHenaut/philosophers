/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghenaut- <ghenaut-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 23:22:07 by ghenaut-          #+#    #+#             */
/*   Updated: 2022/08/26 15:48:37 by ghenaut-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	error(int error_code)
{
	if (error_code == 1)
		write(2, ERROR_1, ERROR_1_SIZE);
	if (error_code == 2)
		write(2, ERROR_2, ERROR_2_SIZE);
	if (error_code == 3)
		write(2, ERROR_3, ERROR_3_SIZE);
	return (1);
}
