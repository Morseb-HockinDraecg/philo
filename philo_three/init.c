#include "philo.h"

static void	init_semaphore(t_philo *p)
{
	sem_unlink("/print");
	p->print = sem_open("/print", O_CREAT, S_IRWXU, 1);
	p->forks = NULL;
	sem_unlink("/forks");
	p->forks = sem_open("/forks", O_CREAT, S_IRWXU, p->nb);
}

static void	close_semaphore(t_philo *p)
{
	sem_close(p->forks);
	sem_close(p->print);
}

static int	init_philo_list(t_philo *p)
{
	int	i;

	i = p->nb;
	p->philo_last_action = (int *)malloc(sizeof(int) * i);
	p->philo_last_meal = (int *)malloc(sizeof(int) * i);
	p->philo_last_meal_tmp = (int *)malloc(sizeof(int) * i);
	if (!p->philo_last_action || !p->philo_last_meal || !p->philo_last_meal_tmp)
	{
		write(2, "malloc failed !\n", ft_strlen("malloc failed !\n"));
		return (1);
	}
	while (i--)
	{
		p->philo_last_meal[i] = get_time(p);
		p->philo_last_meal_tmp[i] = 0;
		p->philo_last_action[i] = -1;
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
	p->die = ft_atoi(argv[2]);
	p->eat = ft_atoi(argv[3]);
	p->sleep = ft_atoi(argv[4]);
	if (argc == 6)
		p->turns = ft_atoi(argv[5]);
	else
		p->turns = -1;
	p->start = 0;
	p->start = get_time(p);
	init_semaphore(p);
	// pthread_manag(p, init_philo_list(p));
	process_manag(p, init_philo_list(p));
	close_semaphore(p);
	free_mallocs(p);
	return (E_SUCCESS);
}
