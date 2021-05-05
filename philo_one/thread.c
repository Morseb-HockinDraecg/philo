#include "philo.h"

static void	treatment(t_philo *p, int philo_n)
{
	int	i;
	int	fill[2];

	if (philo_n % 2)
	{
		fill[0] = 1;
		fill[1] = 0;
	}
	else
	{
		fill[0] = 0;
		fill[1] = 1;
	}
	i = p->nb;
	while (i--)
	{
		if (i % 2)
			p->philo_need_to_eat[i] = fill[0];
		else
			p->philo_need_to_eat[i] = fill[1];
	}
}

static void	refrech_list(t_philo *p, int philo_n)
{
	int	i;

	pthread_mutex_lock(&p->print);
	p->philo_need_to_eat[philo_n - 1] = 0;
	i = p->nb;
	while (i--)
	{
		if (p->philo_need_to_eat[i] == 1)
			break ;
	}
	if (i == -1)
		treatment(p, philo_n);
	pthread_mutex_unlock(&p->print);
}

static void	philo_loop(t_philo *p, int philo_n)
{
	int	action;

	action = chosing_action(p, philo_n);
	if (action == -1)
		return ;
	p->philo_last_meal_tmp[philo_n - 1] = get_time(p);
	print_msg("is eating\n", p, philo_n, E_EAT);
	usleep(p->eat);
	p->philo_last_meal[philo_n - 1] = get_time(p);
	refrech_list(p, philo_n);
	print_msg("is sleeping\n", p, philo_n, E_SLEEP);
	usleep(p->sleep);
	print_msg("is thinking\n", p, philo_n, E_THINK);
}

static void	*routine(void *pt)
{
	int		turns;
	int		philo_n;
	t_philo	*p;

	p = (t_philo *)pt;
	pthread_mutex_lock(&p->print);
	philo_n = p->init_philo--;
	turns = p->turns;
	pthread_mutex_unlock(&p->print);
	while (turns-- && p->die)
		philo_loop(p, philo_n);
	pthread_mutex_lock(&p->print);
	p->finished++;
	pthread_mutex_unlock(&p->print);
	return (NULL);
}

void	pthread_manag(t_philo *p, int stop)
{
	pthread_t	*th;
	int			i;

	if (stop)
		return ;
	p->init_philo = p->nb;
	th = (pthread_t *)malloc(sizeof(pthread_t) * p->nb);
	i = -1;
	while (++i < p->nb)
		pthread_create(th + i, NULL, &routine, p);
	loop_ckecking_dying_philo(p);
	i = -1;
	while (++i < p->nb)
		pthread_join(th[i], NULL);
	free(th);
}
