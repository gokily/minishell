#include "minishell.h"
#include <stdio.h>

int		print_cmd(t_cmd cmd)
{
	t_lcmd *elem;

	elem = cmd.head;
	while (elem != NULL)
	{
		printf("elem has |%s| in it\n", elem->str);
		elem = elem->next;
	}
	return (1);
}