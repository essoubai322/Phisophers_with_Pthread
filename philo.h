/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebaai <asebaai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 11:17:45 by asebaai           #+#    #+#             */
/*   Updated: 2024/12/12 11:18:50 by asebaai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

struct	s_table;

typedef struct s_philo
{
	int				id;
	int				is_full;
	int				left_fork_id;
	int				right_fork_id;
	long long		last_meal;
	int				n_meals;
	struct s_table	*table;
	pthread_t		thread;
}					t_philo;

typedef struct s_table
{
	int				n_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				deaths;
	int				all_full;
	int				n_meals;
	long long		start_time;
	pthread_mutex_t	meal_check;
	pthread_mutex_t	forks[1010];
	pthread_mutex_t	write_lock;
	t_philo			philos[1010];
}					t_table;

int					ft_atoi(const char *str);
int					is_valid_digit(char *str);
int					is_args_valid(char **av);
long long			timestamp(void);
long long			time_diff(long long past, long long pres);
void				philos_init(t_table *table);
void				*philo_start(void *arg);
int					table_init(t_table *table, char **av);
void				print_action(t_table *table, int philo_id, char *action);
void				safe_sleep(long long time, t_table *table);
void				philo_eat(t_philo *philo);
void				watch_dog(t_table *table, t_philo *philos);
void				exit_sim(t_table *table, t_philo *philos);
int					start_sim(t_table *table);

#endif
