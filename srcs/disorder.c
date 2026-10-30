#include "push_swap.h"

long	compute_disorder(t_stack *s)
{
	int		i;
	int		j;
	long	inversions;
	long	pairs;

	if (s->size < 2)
		return (0);
	inversions = 0;
	i = 0;
	while (i < s->size)
	{
		j = i + 1;
		while (j < s->size)
		{
			if (s->val[i] > s->val[j])
				inversions++;
			j++;
		}
		i++;
	}
	pairs = (long)s->size * (s->size - 1) / 2;
	return (inversions * 10000 / pairs);
}

int	is_sorted(t_stack *s)
{
	int	i;

	i = 0;
	while (i < s->size - 1)
	{
		if (s->val[i] > s->val[i + 1])
			return (0);
		i++;
	}
	return (1);
}
