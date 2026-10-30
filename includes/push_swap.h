#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdlib.h>
# include "libft.h"

typedef enum e_strategy
{
	SIMPLE,
	MEDIUM,
	COMPLEX,
	ADAPTIVE
}	t_strategy;

int		parse_flags(int argc, char **argv, t_strategy *strategy, int *bench);
int		*index_values(int *tab, int size);
double	compute_disorder(int *tab, int size);

#endif
