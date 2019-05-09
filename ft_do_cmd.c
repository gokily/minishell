#include <unistd.h>
#include "libft/incl/ft_printf.h"
#include "minishell.h"


int		ft_do_cmd(t_gcmd *cmd)
{
	t_lcmd *elem;
	int		i;

	if (cmd->flag & QUOTE)
		write(STDOUT_FILENO, "oups\n", 5);
	else
	{
		write(STDOUT_FILENO, "YAYA\n", 5);
		elem = cmd->head;
		i = 0;
		while (elem != NULL)
		{
			ft_printf("cmd n%02d is is %s\n", i, elem->cmd);
			elem = elem->next;
			i++;
		}
	}
	ft_reset_cmd(cmd);
	return (0);
}