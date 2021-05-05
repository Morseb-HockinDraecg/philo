#include "philo.h"

static void	init_forks(t_philo *p)
{
	int				i;

	i = p->nb;
	p->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * i);
	if (!p->forks)
	{
		write(2, "mutex malloc failed!\n", ft_strlen("mutex malloc failed !\n"));
		return ;
	}
	while (i--)
		pthread_mutex_init(&(p->forks[i]), NULL);
}

static int	init_philo_list(t_philo *p)
{
	int	i;

	i = p->nb;
	p->philo_need_to_eat = (int *)malloc(sizeof(int) * i);
	p->philo_last_action = (int *)malloc(sizeof(int) * i);
	p->philo_last_meal = (int *)malloc(sizeof(int) * i);
	p->philo_last_meal_tmp = (int *)malloc(sizeof(int) * i);
	if (!p->philo_need_to_eat || !p->philo_last_action || !p->philo_last_meal \
	|| !p->philo_last_meal_tmp)
	{
		write(2, "malloc failed !\n", ft_strlen("malloc failed !\n"));
		return (1);
	}
	while (i--)
	{
		p->philo_last_meal[i] = get_time(p);
		p->philo_last_meal_tmp[i] = 0;
		p->philo_last_action[i] = -1;
		if (i % 2)
			p->philo_need_to_eat[i] = 1;
		else
			p->philo_need_to_eat[i] = 0;
	}
	p->finished = 0;
	return (0);
}

int	init(int argc, char **argv, t_philo *p)
{
	int	i;

	p->nb = ft_atoi(argv[1]);
	i = p->nb;
	if (!i)
		return (E_FAIL);
	pthread_mutex_init(&p->print, NULL);
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
	pthread_manag(p, init_philo_list(p));
	while (i--)
		pthread_mutex_destroy(&(p->forks[i]));
	pthread_mutex_destroy(&p->print);
	free_mallocs(p);
	return (E_SUCCESS);
}
