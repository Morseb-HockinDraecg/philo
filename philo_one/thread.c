#include "philo.h"

static void	refrech_list(t_philo *p, int philo_n)
{
	int	i;
	int	fill[2];

	pthread_mutex_lock(&p->print);
	p->philo_need_to_eat[philo_n - 1] = 0;
	i = p->nb;
	while (i--)
	{
		if (p->philo_need_to_eat[i] == 1)
			break ;
	}
	if (i == 0)
	{
		i = p->nb;
		if (philo_n % 2)
		{
			fill[0] = 0;
			fill[1] = 1;
		}
		else
		{
			fill[0] = 1;
			fill[1] = 0;
		}
		while (i--)
		{
			if (i % 2)
				p->philo_need_to_eat[i] = fill[0];
			else
				p->philo_need_to_eat[i] = fill[1];
		}
	}
	pthread_mutex_unlock(&p->print);
}

static void	philo_loop(t_philo *p, int philo_n)
{
	int	action;

	action = chosing_action(p, philo_n);
	refrech_list(p, philo_n);
	print_msg("is eating\n", p, philo_n);
	usleep(p->eat);
	// print_msg("is sleeping\n", p, philo_n);
	// usleep(p->sleep);
	// print_msg("is thinking\n", p, philo_n);
}

static void	*routine(void *pt)
{
	int		turns;
	int		philo_n;
	t_philo	*p;

	p = (t_philo *)pt;
	philo_n = p->init_philo--;
	turns = p->turns;
	while (turns-- && p->die)
		philo_loop(p, philo_n);
	return (NULL);
}

void	pthread_manag(t_philo *p)
{
	pthread_t	*th;
	int			i;

	p->init_philo = p->nb;
	th = (pthread_t *)malloc(sizeof(pthread_t) * p->nb);
	i = -1;
	while (++i < p->nb)
		pthread_create(th + i, NULL, &routine, p);
	i = -1;
	while (++i < p->nb)
		pthread_join(th[i], NULL);
	free(th);
}
