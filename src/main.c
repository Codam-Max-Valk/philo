/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvalk <mvalk@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/24 15:24:09 by mvalk         #+#    #+#                 */
/*   Updated: 2023/10/24 16:57:50 by mvalk         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	join_philo(t_params *s_data)
{
	size_t	i;

	i = 0;
	while (i < s_data->philo_count)
	{
		pthread_join(s_data->philos[i], NULL);
		i++;
	}
	return (0);
}

void lk()
{
	system("leaks -q philo");
}

int	main(int ac, char **av)
{
	t_params	s_data;

	atexit(lk);
	if (ac == 5 || ac == 6)
	{
		if (check_input_type(av))
			return (printf("Error, invalid argument\n"), EINVAL);
		if (init_philosophers(ac, av, &s_data))
			return (printf("Error, invalid argument\n"), EINVAL);
		if (init_params(&s_data))
			return (ENOMEM);
		philosophers(&s_data);
		join_philo(&s_data);
		return (free(s_data.eat_count), free(s_data.forks),
			free(s_data.philos), free(s_data.ph_par), EXIT_SUCCESS);
	}
	else
	{
		printf("Error, invalid argument count\n");
		return (EXIT_FAILURE);
	}
}
