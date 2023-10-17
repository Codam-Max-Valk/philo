/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvalk <mvalk@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/27 17:16:18 by mvalk         #+#    #+#                 */
/*   Updated: 2023/10/17 17:50:21 by mvalk         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	gettime_dif(struct timeval start_time)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return ((current_time.tv_sec * 1000 + current_time.tv_usec / 1000)
		- (start_time.tv_sec * 1000 + start_time.tv_usec / 1000));
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	ptr = malloc(count * size);
	if (!ptr)
		return (NULL);
	memset(ptr, 0, count * size);
	return (ptr);
}

void	ph_sleep(size_t naptime, t_philo *philo)
{
	struct timeval	start_time;

	gettimeofday(&start_time, NULL);
	while (gettime_dif(start_time) < naptime)
	{
		usleep(250);
		if (philo != NULL)
		{
			if (ac_check_death(philo) == true)
				return ;
		}
	}
}

bool	check_stop(t_philo *philo)
{
	pthread_mutex_lock(&philo->s_data->eat_c);
	if (gettime_dif(philo->last_eaten) >= philo->s_data->time_to_die)
	{
		pthread_mutex_unlock(&philo->s_data->eat_c);
		pthread_mutex_lock(&philo->s_data->death_c);
		philo->s_data->is_dead = true;
		pthread_mutex_unlock(&philo->s_data->death_c);
		pthread_mutex_lock(&philo->s_data->print_c);
		printf("%zu %zu %s\n", gettime_dif(philo->s_data->start_time),
			philo->philo_id + 1, DIED);
		pthread_mutex_unlock(&philo->s_data->print_c);
		return (true);
	}
	pthread_mutex_unlock(&philo->s_data->eat_c);
	return (false);
}

bool	set_stop_eat(t_params *s_data)
{
	size_t	i;

	i = 0;
	pthread_mutex_lock(&s_data->eat_c);
	while (i < s_data->philo_count)
	{
		if (s_data->eat_count[i] < s_data->max_eat)
		{
			pthread_mutex_unlock(&s_data->eat_c);
			return (false);
		}
		i++;
	}
	pthread_mutex_lock(&s_data->death_c);
	s_data->is_dead = true;
	pthread_mutex_unlock(&s_data->death_c);
	pthread_mutex_unlock(&s_data->eat_c);
	return (true);
}
