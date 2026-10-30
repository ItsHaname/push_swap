#include "push_swap.h"

static int	set_flag(char *arg, t_strategy *strategy, int *bench)
{
	if (!ft_strncmp(arg, "--simple", 9))
		*strategy = SIMPLE;
	else if (!ft_strncmp(arg, "--medium", 9))
		*strategy = MEDIUM;
	else if (!ft_strncmp(arg, "--complex", 10))
		*strategy = COMPLEX;
	else if (!ft_strncmp(arg, "--adaptive", 11))
		*strategy = ADAPTIVE;
	else if (!ft_strncmp(arg, "--bench", 8))
		*bench = 1;
	else
		return (0);
	return (1);
}

int	parse_flags(int argc, char **argv, t_strategy *strategy, int *bench)
{
	int	i;

	*strategy = ADAPTIVE;
	*bench = 0;
	i = 1;
	while (i < argc && argv[i][0] == '-' && argv[i][1] == '-')
	{
		if (!set_flag(argv[i], strategy, bench))
			return (-1);
		i++;
	}
	return (i);
}
