/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvalk <mvalk@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/27 13:58:57 by mvalk         #+#    #+#                 */
/*   Updated: 2023/10/24 14:05:51 by mvalk         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	lock_fork(t_philo *philo, t_lock e_lock, t_fork side)
{
	if (e_lock == lock)
		return (pthread_mutex_lock(&philo->s_data->forks[(philo->philo_id
						+ side) % philo->s_data->philo_count]));
	else if (e_lock == unlock)
		return (pthread_mutex_unlock(&philo->s_data->forks[(philo->philo_id
						+ side) % philo->s_data->philo_count]));
	else
		return (-1);
}

void	*ph_thread(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	pthread_mutex_lock(&philo->s_data->start_lock);
	pthread_mutex_unlock(&philo->s_data->start_lock);
	if ((philo->philo_id) % 2 == 0)
	{
		ac_print(philo, IS_THINKING);
		ph_sleep(philo->s_data->time_to_eat / 2, philo);
	}
	while (true)
	{
		if (ac_hungry(philo) == true)
			ac_eat(philo);
		else
			return (NULL);
		ac_sleep(philo);
		if (ac_print(philo, IS_THINKING) == false)
			return (NULL);
	}
	return (NULL);
}

void	check_death(t_params *s_data)
{
	size_t	i;

	ph_sleep(s_data->time_to_die / 2, NULL);
	while (true)
	{
		i = 0;
		while (i < s_data->philo_count)
		{
			if (check_stop(&s_data->ph_par[i]) == true)
				return ;
			i++;
		}
		if (s_data->eat_limit == true)
			if (set_stop_eat(s_data) == true)
				break ;
		ph_sleep(1, NULL);
	}
}

int	philosophers(t_params *s_data)
{
	size_t	i;

	i = 0;
	pthread_mutex_lock(&s_data->start_lock);
	while (i < s_data->philo_count)
	{
		s_data->ph_par[i].s_data = s_data;
		if (s_data->eat_limit == true)
			s_data->ph_par[i].eat_limit = true;
		s_data->ph_par[i].philo_id = i;
		pthread_create(&s_data->philos[i], NULL, ph_thread, &s_data->ph_par[i]);
		i++;
	}
	gettimeofday(&s_data->start_time, NULL);
	i = 0;
	while (i < s_data->philo_count)
	{
		s_data->ph_par[i].last_eaten = s_data->start_time;
		i++;
	}
	pthread_mutex_unlock(&s_data->start_lock);
	check_death(s_data);
	return (0);
}
