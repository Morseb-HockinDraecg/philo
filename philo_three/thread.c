#include "philo.h"

static void	philo_loop(t_philo *p, int philo_n)
{
	int	id;

	id = chosing_action(p, philo_n);
	if (id == -1)
		return ;
	print_msg("\e[31mhas taken a fork\e[00m\n", p, philo_n, E_FORK_2);
	print_msg("\e[32mis eating\e[00m\n", p, philo_n, E_EAT);
	p->philo_last_meal_tmp[philo_n - 1] = get_time(p) + 5;
	usleep(p->eat * 1000);
	sem_post(&p->forks[philo_n - 1]);
	sem_post(&p->forks[id]);
	print_msg("is sleeping\n", p, philo_n, E_SLEEP);
	usleep(p->sleep * 1000);
	print_msg("is thinking\n", p, philo_n, E_THINK);
}

static void	*routine(void *pt)
{
	int		turns;
	int		philo_n;
	t_philo	*p;

	p = (t_philo *)pt;
	sem_wait(p->print);
	philo_n = p->init_philo--;
	turns = p->turns;
	sem_post(p->print);
	while (turns-- && p->die)
		philo_loop(p, philo_n);
	sem_wait(p->print);
	p->finished++;
	sem_post(p->print);
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
