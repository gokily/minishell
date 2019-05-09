#include "minishell.h"
#include <stdio.h>

int		print_input(t_input input)
{
	t_linput *elem;

	elem = input.head;
	while (elem != NULL)
	{
		printf("elem has |%s| in it\n", elem->str);
		elem = elem->next;
	}
	return (1);
}