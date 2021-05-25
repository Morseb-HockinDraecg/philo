#include "philo.h"

int	main(int argc, char **argv)
{
	t_philo		p;

	if (!(argc == 5 || argc == 6))
		return (write(STDOUT_FILENO, "Wrong numbers of arg !\n", \
		ft_strlen("Wrong numbers of arg !\n")));
	if (ft_atoi(argv[1]) < 2)
	{
		printf("Mini 2 philo !\n");
		return (E_FAIL);
	}
	if (init(argc, argv, &p) == -1)
		return (E_FAIL);
	return (E_SUCCESS);
}
