#include "philo.h"

int	loop_ckecking_dying_philo(t_philo *p)
{
	int	i;

	i = p->init_philo - 1;
	while (p->die && p->finished != 1)
	{
		p->philo_last_meal[i] = get_time(p) - p->philo_last_meal_tmp[i];
		if (p->philo_last_meal[i] >= p->die)
		{
			sem_wait(p->print);
			p->die = 0;
			printf("%4ld %d %s", get_time(p), (i + 1), "died\n");
			exit(1);
		}
	}
	return (0);
}

static void	chosing_action_algo(t_philo *p, int philo_n, int *has_eat)
{
	int			i;
	int			philo;

	philo = philo_n - 1;
	if (philo_n % 2)
		usleep(81);
	sem_wait(p->forks);
	print_msg("\e[33mhas taken a fork\e[00m\n", p, philo_n, E_FORK);
	i = philo_n % p->nb;
	sem_wait(p->forks);
	*has_eat = i;
}

int	chosing_action(t_philo *p, int philo_n)
{
	int			has_eat;

	has_eat = -1;
	while (has_eat < 0)
	{
		print_msg("is thinking\n", p, philo_n, E_THINK);
		if (!p->die)
			return (-1);
		chosing_action_algo(p, philo_n, &has_eat);
	}
	return (has_eat);
}
