#include <stdlib.h>
#include "minishell.h"
#include "libft/libft.h"

static t_linput	*ft_linput_new(char *str, int flag)
{
	t_linput		*elem;

	if (!(elem = malloc(sizeof(t_linput))))
		return (NULL);
	elem->next = NULL;
	elem->flag = flag;
	elem->str = str;
	return (elem);
}

int	ft_add_linput(char *str, t_input *input, int flag)
{
	t_linput		*elem;

	if (flag & LAST)
	{
		elem = input->end;
		elem->str = ft_strjoinfree(elem->str, str, LEFT | RIGHT);
		if (elem->str == NULL)
			return (-1);
		input->end = elem;
	}
	else
	{
		if (!(elem = ft_linput_new(str, flag)))
			return (-1);
		if (input->head == NULL)
			input->head = elem;
		else
			input->end->next = elem;
		input->end = elem;
	}
	return (1);
}
