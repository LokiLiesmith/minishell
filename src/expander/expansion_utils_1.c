#include "minishell.h"

void	init_exp_struct(t_exp *exp)
{
	exp->i = 0;
	exp->count = 0;
	exp->in_sq = false;
	exp->in_dq = false;
}

void update_quotes(char c, bool *in_sq, bool *in_dq)
{
	if (!*in_dq && c == '\'')
		*in_sq = !*in_sq;
	else if (!*in_sq && c == '"')
		*in_dq = !*in_dq;
}

int calc_quotes(bool in_sq, bool in_dq)
{
	if (in_dq)
		return (2);
	else if (in_sq)
		return (1);
	return (0);
}

void increment_counters(int *i, int *b)
{
	(*i)++;
	(*b)++;
}