#include <stdlib.h>
#include "minishell.h"
#include "libft/libft.h"

static t_lcmd	*ft_lcmd_new(char *str, int flag)
{
	t_lcmd		*elem;

	if (!(elem = malloc(sizeof(t_lcmd))))
		return (NULL);
	elem->next = NULL;
	elem->flag = flag;
	elem->str = str;
	return (elem);
}

int	ft_add_lcmd(char *str, t_cmd *cmd, int flag)
{
	t_lcmd		*elem;

puts("in add lcmd");
	if (flag & LAST)
	{
		puts("adding to the last elem");
		elem = cmd->end;
		elem->str = ft_strjoinfree(elem->str, str, LEFT | RIGHT);
		if (elem->str == NULL)
			return (-1);
		cmd->end = elem;
	}
	else
	{
		puts("new elem");
		if (!(elem = ft_lcmd_new(str, flag)))
			return (-1);
		if (cmd->head == NULL)
			cmd->head = elem;
		else
			cmd->end->next = elem;
		cmd->end = elem;
	}
	return (1);
}
