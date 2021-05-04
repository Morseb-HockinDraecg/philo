#include "philo.h"

static void	print_philo(t_philo *p, int philo_n, int action)
{
	if (action == E_FORK)
		print_msg("has taken a fork\n", p, philo_n);
	else if (action == E_THINK)
		print_msg("is thinking\n", p, philo_n);
	else if (action == E_DIE)
	{
		print_msg("died\n", p, philo_n);
		p->die = 0;
		// pthread_detach(p->forks);
		// free_mallocs(p);
		// exit(0);
	}
}

static int	chosen_index(t_philo *p)
{
	int	i;

	i = 0;
	while (p->philo_need_to_eat[i] != 0 && i < (p->nb))
			i++;
	if (i == p->nb)
		chosen_index(p);
	return (i);
}

// int	chosing_action(t_philo *p, int philo_n)
static void	chosing_action_algo(t_philo *p, int philo_n, int *has_eat)
{
	int			i;
	static int	action = -1;

	if (p->philo_need_to_eat[philo_n - 1] == 1)
	{
		pthread_mutex_lock(&p->forks[philo_n - 1]);
		i = chosen_index(p);
		pthread_mutex_lock(&p->forks[i]);
		pthread_mutex_lock(&p->print);
		p->philo_need_to_eat[i] = 2;
		pthread_mutex_unlock(&p->print);
		if (action != E_FORK)
		{
			print_philo((t_philo *)p, philo_n, E_FORK);
			action = E_THINK;
		}
		*has_eat = 1;
		pthread_mutex_unlock(&p->forks[philo_n - 1]);
		pthread_mutex_unlock(&p->forks[i]);
	}
	if (action != E_THINK)
	{
		action = E_THINK;
		print_philo((t_philo *)p, philo_n, E_THINK);
	}
}

int	chosing_action(t_philo *p, int philo_n)
{
	int			has_eat;

	has_eat = 0;
	while (!has_eat)
		chosing_action_algo(p, philo_n, &has_eat);
	return (E_EAT);
}