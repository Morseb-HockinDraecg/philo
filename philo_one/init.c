#include "philo.h"

static void	init_forks(t_philo *p)
{
	int				i;

	i = p->nb;
	p->forks = NULL;
	p->forks = (pthread_mutex_t *)malloc \
	(sizeof(pthread_mutex_t) * i);
	if (!p->forks)
	{
		write(2, "mutex malloc failed!\n", ft_strlen("mutex malloc failed !\n"));
		return ;
	}
	while (i--)
		pthread_mutex_init(&(p->forks[i]), NULL);
}

static void	init_philo_need_to_eat(t_philo *p)
{
	int	i;

	i = p->nb;
	p->philo_need_to_eat = NULL;
	p->philo_need_to_eat = (int *)malloc(sizeof(int) * i);
	if (!p->philo_need_to_eat)
	{
		write(2, "malloc failed !\n", ft_strlen("malloc failed !\n"));
		return ;
	}
	while (i--)
	{
		if (i % 2)
			p->philo_need_to_eat[i] = 1;
		else
			p->philo_need_to_eat[i] = 0;
	}
}

int	init(int argc, char **argv, t_philo *p)
{
	int	i;

	pthread_mutex_init(&p->print, NULL);
	p->nb = ft_atoi(argv[1]);
	i = p->nb;
	if (!i)
		return (E_FAIL);
	p->die = ft_atoi(argv[2]);
	p->eat = ft_atoi(argv[3]);
	p->sleep = ft_atoi(argv[4]);
	if (argc == 6)
		p->turns = ft_atoi(argv[5]);
	else
		p->turns = -1;
	p->start = 0;
	p->start = get_time(p);
	init_forks(p);
	init_philo_need_to_eat(p);
	pthread_manag(p);
	while (i--)
		pthread_mutex_destroy(&(p->forks[i]));
	pthread_mutex_destroy(&p->print);
	free_mallocs(p);
	return (E_SUCCESS);
}
