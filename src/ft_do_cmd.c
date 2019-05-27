#include <unistd.h>
#include "libft.h"
#include "minishell.h"


#include "ft_printf.h"

int		ft_do_cmd(t_gcmd *cmd)
{
	t_lcmd *elem;
	int		i;
	char	**cmd_tab;
	char	*path;

	elem = cmd->head;
	i = -1;
	path = NULL;
	while (elem != NULL)
	{
		cmd_tab = ft_cmdsplit(elem->cmd);
		if ((i = ft_find_builtin(cmd_tab[0])) != -1)
			ft_serve_builtin(i, cmd_tab, cmd); // return value ?
		else
		{
			if (ft_strchr(cmd_tab[0], '/'))
			{
				if (ft_exec_cmd_direct(cmd_tab, cmd->envp) == -1)
					return (-1);
			}
			else if ((ft_search_path(cmd_tab[0], &path, cmd->envp)) == -1)
				return (-1);
			else if (path != NULL)
			{
				if (ft_exec_cmd_from_path(cmd_tab, path, cmd->envp) == -1)
					return (-1);
			}
		}

		elem = elem->next;
	}
	ft_reset_cmd(cmd);
	return (0);
}