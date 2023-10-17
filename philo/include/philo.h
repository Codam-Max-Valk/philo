/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvalk <mvalk@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/24 15:24:37 by mvalk         #+#    #+#                 */
/*   Updated: 2023/10/17 17:51:28 by mvalk         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <errno.h>
# include <pthread.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

// STRUCT DEFINES

typedef struct s_philo	t_philo;

# define TAKEN_FORK "has taken a fork"
# define IS_EATING "is eating"
# define IS_SLEEPING "is sleeping"
# define IS_THINKING "is thinking"
# define DIED "died"

typedef enum e_lock_wrap
{
	lock,
	unlock
}	t_lock;

typedef enum e_fork_wrap
{
	left,
	right
}	t_fork;

typedef struct s_data
{
	size_t				max_eat;
	size_t				philo_count;
	size_t				time_to_die;
	size_t				time_to_sleep;
	size_t				time_to_eat;
	struct timeval		start_time;
	pthread_mutex_t		death_c;
	pthread_mutex_t		print_c;
	pthread_mutex_t		eat_c;
	pthread_mutex_t		start_lock;
	bool				is_dead;
	bool				eat_limit;
	pthread_t			*philos;
	pthread_mutex_t		*forks;
	t_philo				*ph_par;
	size_t				*eat_count;
}						t_params;

typedef struct s_philo
{
	struct timeval		last_eaten;
	size_t				philo_id;
	bool				eat_limit;
	t_params			*s_data;
}						t_philo;

// UTILS

size_t					gettime_dif(struct timeval start_time);
void					*ft_calloc(size_t count, size_t size);
int32_t					ft_atoi(const char *str);
bool					set_stop_eat(t_params *s_data);
int						lock_wrap(t_philo *philo, t_lock e_lock, t_fork side);
// FUNCTIONS

int						philosophers(t_params *s_data);
void					ph_sleep(size_t naptime, t_philo *philo);
// void	ph_sleep(size_t naptime);
int						check_input_type(char **input);
int						init_philosophers(int ac, char **av, t_params *s_data);
void					init_forks(t_params *s_data);
int						init_params(t_params *s_data);

// ACTIONS

bool					check_stop(t_philo *philo);
// void					ac_check_eatc(t_philo *philo);

// bool					ac_check_eatc(t_philo *philo);
bool					ac_check_death(t_philo *philo);
bool					ac_print(t_philo *philo, const char *action);

// bool	ac_print(t_philo *philo, t_print print);
void					ac_eat(t_philo *philo);
void					ac_sleep(t_philo *philo);
int						ac_hungry(t_philo *philo);

#endif
