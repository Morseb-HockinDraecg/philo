#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdlib.h>
# include <semaphore.h>

typedef struct s_philo
{
	int				nb;
	int				die;
	int				eat;
	int				sleep;
	int				turns;
	long			start;
	int				init_philo;
	int				finished;
	sem_t			*print;
	sem_t			*forks;
	int				*philo_need_to_eat;
	int				*philo_last_action;
	int				*philo_last_meal;
	int				*philo_last_meal_tmp;
}	t_philo;

enum	e_action
{
	E_FORK,
	E_FORK_2,
	E_EAT,
	E_SLEEP,
	E_THINK,
	E_DIE,
};

enum	e_retrun
{
	E_SUCCESS,
	E_FAIL,
};

void		pthread_manag(t_philo *p, int stop);

int			chosing_action(t_philo *p, int philo_n);

int			ft_atoi(const char *nptr);
int			ft_strlen(char *s);
int			init(int argc, char **argv, t_philo *philo);
void		free_mallocs(t_philo *p);
long int	get_time(t_philo *p);
void		print_msg(const char *s, t_philo *p, int philo_n, int action);
void		loop_ckecking_dying_philo(t_philo *p);

#endif