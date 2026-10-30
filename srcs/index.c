#include "push_swap.h"

static int	rank_of(t_stack *s, int i)
{
	int	j;
	int	count;

	count = 0;
	j = 0;
	while (j < s->size)
	{
		if (s->val[j] < s->val[i])
			count++;
		j++;
	}
	return (count);
}

void	assign_index(t_ctx *ctx)
{
	int	*index;
	int	i;

	index = malloc(sizeof(int) * ctx->a.size);
	if (!index)
		error_exit(ctx);
	i = 0;
	while (i < ctx->a.size)
	{
		index[i] = rank_of(&ctx->a, i);
		i++;
	}
	free(ctx->a.val);
	ctx->a.val = index;
}
