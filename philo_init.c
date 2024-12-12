/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebaai <asebaai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 11:18:20 by asebaai           #+#    #+#             */
/*   Updated: 2024/12/12 11:18:59 by asebaai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philos_init(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->n_philos)
	{
		table->philos[i].id = i;
		table->philos[i].is_full = 0;
		table->philos[i].left_fork_id = i;
		table->philos[i].right_fork_id = (i + 1) % table->n_philos;
		table->philos[i].last_meal = 0;
		table->philos[i].table = table;
		i++;
	}
}

void	*philo_start(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2)
		usleep(1200);
	while (!(philo->table->deaths))
	{
		philo_eat(philo);
		if (philo->table->all_full)
			break ;
		print_action(philo->table, philo->id, "is sleeping");
		safe_sleep(philo->table->time_to_sleep, philo->table);
		print_action(philo->table, philo->id, "is thinking");
	}
	return (NULL);
}

int	table_init(t_table *table, char **av)
{
	int	i;

	i = 0;
	table->n_philos = ft_atoi(av[1]);
	table->time_to_die = ft_atoi(av[2]);
	table->time_to_eat = ft_atoi(av[3]);
	table->time_to_sleep = ft_atoi(av[4]);
	table->all_full = 0;
	table->deaths = 0;
	if (av[5])
		table->n_meals = ft_atoi(av[5]);
	else
		table->n_meals = -1;
	if (pthread_mutex_init(&(table->write_lock), NULL))
		return (1);
	if (pthread_mutex_init(&(table->meal_check), NULL))
		return (1);
	while (i < table->n_philos)
	{
		if (pthread_mutex_init(&(table->forks[i]), NULL))
			return (1);
		i++;
	}
	return (0);
}

void	print_action(t_table *table, int philo_id, char *action)
{
	pthread_mutex_lock(&(table->write_lock));
	if (!(table->deaths))
		printf("%lli %i %s\n", timestamp() - table->start_time, philo_id + 1,
			action);
	pthread_mutex_unlock(&(table->write_lock));
	return ;
}

void	safe_sleep(long long time, t_table *table)
{
	long long	sleep_start;

	sleep_start = timestamp();
	while (!(table->deaths))
	{
		if (time_diff(sleep_start, timestamp()) >= time)
			break ;
		usleep(50);
	}
}
