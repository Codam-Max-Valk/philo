/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_actions.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvalk <mvalk@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/03 13:49:33 by mvalk         #+#    #+#                 */
/*   Updated: 2023/10/24 14:05:51 by mvalk         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	ac_check_death(t_philo *philo)
{
	pthread_mutex_lock(&philo->s_data->death_c);
	if (philo->s_data->is_dead == true)
	{
		pthread_mutex_unlock(&philo->s_data->death_c);
		return (true);
	}
	pthread_mutex_unlock(&philo->s_data->death_c);
	return (false);
}

bool	ac_print(t_philo *philo, const char *action)
{
	pthread_mutex_lock(&philo->s_data->print_c);
	if (ac_check_death(philo) == true)
	{
		pthread_mutex_unlock(&philo->s_data->print_c);
		return (false);
	}
	printf("%zu %zu %s\n", gettime_dif(philo->s_data->start_time),
		philo->philo_id + 1, action);
	pthread_mutex_unlock(&philo->s_data->print_c);
	return (true);
}

void	ac_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->s_data->eat_c);
	gettimeofday(&philo->last_eaten, NULL);
	philo->s_data->eat_count[philo->philo_id]++;
	pthread_mutex_unlock(&philo->s_data->eat_c);
	if (ac_print(philo, IS_EATING) == false)
	{
		lock_fork(philo, unlock, left);
		lock_fork(philo, unlock, right);
		return ;
	}
	ph_sleep(philo->s_data->time_to_eat, philo);
	lock_fork(philo, unlock, left);
	lock_fork(philo, unlock, right);
}

void	ac_sleep(t_philo *philo)
{
	size_t	sleep_time;

	sleep_time = philo->s_data->time_to_sleep;
	if (ac_print(philo, IS_SLEEPING) == false)
		return ;
	ph_sleep(sleep_time, philo);
}

int	ac_hungry(t_philo *philo)
{
	lock_fork(philo, lock, left);
	if (ac_print(philo, TAKEN_FORK) == false)
		return (lock_fork(philo, unlock, left), false);
	if (philo->s_data->philo_count == 1)
		return (ph_sleep(philo->s_data->time_to_die / 2, philo),
			lock_fork(philo, unlock, left), false);
	lock_fork(philo, lock, right);
	if (ac_print(philo, TAKEN_FORK) == false)
		return (lock_fork(philo, unlock, right),
			lock_fork(philo, unlock, left), false);
	return (true);
}
