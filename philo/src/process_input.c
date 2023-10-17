/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   process_input.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvalk <mvalk@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/27 14:05:26 by mvalk         #+#    #+#                 */
/*   Updated: 2023/09/07 15:28:55 by mvalk         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	ft_isdigit(char c)
{
	return (c >= '0' && c <= '9');
}

int	ft_atoi(const char *str)
{
	int		neg;
	long	number;

	neg = 0;
	number = 0;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			neg--;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		number = 10 * number + (*str - 48);
		str++;
	}
	if (neg < 0)
		return (neg * number);
	return (number);
}

int	check_input_type(char **input)
{
	int	j;
	int	i;

	i = 1;
	if (ft_atoi(input[i]) > 2047)
		return (1);
	while (input[i] != NULL)
	{
		j = 0;
		if (input[i][j] == '\0')
			return (1);
		while (input[i][j])
		{
			if (!ft_isdigit(input[i][j]))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}
