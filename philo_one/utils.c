#include "philo.h"

int	ft_atoi(const char *nptr)
{
	long long int	val;
	int				signe;

	signe = 1;
	val = 0;
	while (*nptr == ' ' || *nptr == '\t' || *nptr == '\f' || *nptr == '\n' \
		 || *nptr == '\r' || *nptr == '\v')
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			signe = -signe;
		nptr++;
	}
	while ('0' <= *nptr && *nptr <= '9')
		val = 10 * val + (*nptr++ - '0');
	return (signe * val);
}

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	free_mallocs(t_philo *p)
{
	free(p->forks);
	free(p->philo_last_action);
	free(p->philo_last_meal);
}

long int	get_time(t_philo *p)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	if (p->start == 0)
		return (time.tv_sec * 1000 + time.tv_usec / 1000);
	else
		return ((time.tv_sec * 1000 + time.tv_usec / 1000) - p->start);
}

void	print_msg(const char *s, t_philo *p, int philo_n, int action)
{
	int	background;

	background = philo_n % 6;
	pthread_mutex_lock(&p->print);
	if (p->philo_last_action[philo_n - 1] != action && p->die)
	{
		p->philo_last_action[philo_n - 1] = action;
		if (background == 0)
			printf("\e[41m\e[30m%4ld %d\e[49m\e[97m %s", get_time(p), philo_n, s);
		else if (background == 1)
			printf("\e[42m\e[30m%4ld %d\e[49m\e[97m %s", get_time(p), philo_n, s);
		else if (background == 2)
			printf("\e[43m\e[30m%4ld %d\e[49m\e[97m %s", get_time(p), philo_n, s);
		else if (background == 3)
			printf("\e[44m\e[30m%4ld %d\e[49m\e[97m %s", get_time(p), philo_n, s);
		else if (background == 4)
			printf("\e[45m\e[30m%4ld %d\e[49m\e[97m %s", get_time(p), philo_n, s);
		else if (background == 5)
			printf("\e[46m\e[30m%4ld %d\e[49m\e[97m %s", get_time(p), philo_n, s);
	}
	pthread_mutex_unlock(&p->print);
}
