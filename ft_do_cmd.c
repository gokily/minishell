#include <unistd.h>
#include "libft/incl/libft.h"
#include "minishell.h"


#include "libft/incl/ft_printf.h"

/*
int		ft_do_input(void)
{
	pid_t	pid;
	pid_t	wpid;
	int		status;

	status = 0;
	pid = fork();

		if (pid == 0)
		{
			if (ft_strcmp(tab[0], "ls") == 0)
			{
				execve("/bin/ls", tab++, envp);
				printf("ls working\n");
			}
		}
				printf("waiting for child %u to finish\n", pid);
		wpid = waitpid(pid, &status, WUNTRACED);
				printf("child proccess ended, return %u\n", wpid);

}
*/


int		ft_do_cmd(t_gcmd *cmd)
{
	t_lcmd *elem;
	int		i;
	char	**cmd_tab;
	char	*path;

	elem = cmd->head;
	i = 0;
	path = NULL;
	while (elem != NULL)
	{
		cmd_tab = ft_cmdsplit(elem->cmd);

		/*
		if (ft_is_builtin(cmd_tab[0]) == 1)
			ft_serve_builtin(cmd_tab, cmd);
		else
		*/
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
		elem = elem->next;
		i++;
	}
	ft_reset_cmd(cmd);
	return (0);
}