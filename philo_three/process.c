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

	p->init_philo = philo_n;
	pthread_create(&th, NULL, &routine, p);
	loop_ckecking_dying_philo(p);
	pthread_join(th, 0);
	exit(0);
}

static void	normy_pw(t_normy n, t_philo *p)
{
	while (n.pid)
	{
		n.pid = waitpid(-1, &n.wstatus, 0);
		if (errno == ECHILD)
			break ;
		else if (WIFEXITED(n.wstatus))
		{
			n.i = p->nb;
			while (n.i--)
				kill(n.pid_child[n.i], SIGKILL);
		}
	}
}

void	process_manag(t_philo *p, int stop)
{
	t_normy	n;

	if (stop)
		return ;
	p->init_philo = p->nb;
	n.pid_child = (int *)malloc(sizeof(int) * p->nb);
	n.i = -1;
	while (++n.i < p->nb)
	{
		n.pid = fork();
		if (!n.pid)
			break ;
		else
			n.pid_child[n.i] = n.pid;
	}
	if (!n.pid)
		pthread_manag(p, n.i + 1);
	else
		normy_pw(n, p);
	free(n.pid_child);
}
