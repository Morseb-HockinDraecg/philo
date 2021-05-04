#include <stdio.h>
#include <unistd.h>

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	main(int argc, char **argv)
{
	if (!(argc == 5 || argc == 6))
		return (write(STDOUT_FILENO, "Wrong numbers of arg !\n", ft_strlen("Wrong numbers of arg !\n")));
		
	return (0);
}