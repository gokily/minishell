#include <unistd.h>
#include "libft.h"
#include "minishell.h"


#include "ft_printf.h"

int		ft_do_single_cmd(char **cmd_tab, t_gcmd *cmd)
{
	int		i;
	char	*path;
	char	**path_tab;

	path = NULL;
	if ((i = ft_find_builtin(cmd_tab[0])) != -1)
		ft_serve_builtin(i, cmd_tab, cmd); // return value ?
	else
	{
		if (ft_strchr(cmd_tab[0], '/'))
		{
			if (ft_exec_cmd_direct(cmd_tab, cmd->envp) == -1)
				return (-1);
		}
		else
		{
			if (cmd->path == NULL)
				if (ft_create_path_tab(cmd->envp, &path_tab) == -1)
					return (-1);
			ft_search_path(cmd_tab[0], &path, cmd->path ? cmd->path : path_tab);
			if (ft_exec_cmd_from_path(cmd_tab, path, cmd->envp) == -1)
				return (-1);
		}
	}
	return (0);
}

int		ft_do_cmd(t_gcmd *cmd)
{
	t_lcmd *elem;
	char	**cmd_tab;

	elem = cmd->head;
	while (elem != NULL)
	{
		cmd_tab = ft_cmdsplit(elem->cmd);
		if (ft_do_single_cmd(cmd_tab, cmd) == -1)
			return (-1);
		elem = elem->next;
	}
	ft_reset_cmd(cmd);
	return (0);
}