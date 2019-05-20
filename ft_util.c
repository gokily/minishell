#include "minishell.h"

int		ft_check_quote(char c, int flag)
{
	if (c == '"' && !(flag & SQUOT))
	{
		flag ^= DQUOT;
		flag ^= QUOTE;
	}
	else if (c == '\'' && !(flag & DQUOT))
	{
		flag ^= SQUOT;
		flag ^= QUOTE;
	}
	return (flag);
}