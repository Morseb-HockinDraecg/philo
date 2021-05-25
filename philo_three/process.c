#include "philo.h"

static int	philo_loop(t_philo *p, int philo_n)
{
	int	id;

	id = chosing_action(p, philo_n);
	if (id == -1)
		return (-1);
	print_msg("\e[31mhas taken a fork\e[00m\n", p, philo_n, E_FORK_2);
	print_msg("\e[32mis eating\e[00m\n", p, philo_n, E_EAT);
	p->philo_last_meal_tmp[philo_n - 1] = get_time(p) + 5;
	usleep(p->eat * 1000);
	sem_post(p->forks);
	sem_post(p->forks);
	print_msg("is sleeping\n", p, philo_n, E_SLEEP);
	usleep(p->sleep * 1000);
	print_msg("is thinking\n", p, philo_n, E_THINK);
	return (0);
}

static void	*routine(void *pt)
{
	t_philo	*p;
	int		philo_n;
	int		turns;

	p = (t_philo *)pt;
	philo_n = p->init_philo;
	turns = p->turns;
	while (turns-- && p->die)
		philo_loop(p, philo_n);
	p->finished++;
	return (NULL);
}

static int	pthread_manag(t_philo *p, int philo_n)
{
	pthread_t	th;

	p->init_philo = p->nb;
	p->init_philo = philo_n;
	pthread_create(&th, NULL, &routine, p);
	// pthread_detach(th);
	loop_ckecking_dying_philo(p);
	pthread_join(th, 0);
	// return (loop_ckecking_dying_philo(p));
	exit(1);
	return (0);
}

void	process_manag(t_philo *p, int stop)
{
	int			i;
	int			pid;
	int			*pid_child;

	if (stop)
		return ;
	p->init_philo = p->nb;
	i = -1;
	while (++i < p->nb)
	{
		pid = fork();
		if (!pid)
			break ;
		else
			printf("%d\n", pid); //pid de l enfant a stocker dans *pid_child = malloc( nb_philo) puis kill quand retour d un mort
	}
	if (!pid)
	{
		pid = pthread_manag(p, i + 1);
		// if (pid)
		// {
			// kill(0, SIGKILL);
			// sem_post(p->print);
		// }
		// printf("pid : %d\n", pid);
	}
	else
	{
		while (pid)
		{
			pid = waitpid(-1, NULL, 0);
			if (errno == ECHILD)
				break ;
		}
	}
}
