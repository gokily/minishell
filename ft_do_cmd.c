#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "libft/incl/ft_printf.h"
#include "minishell.h"

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

	if (cmd->flag & QUOTE)
		write(STDOUT_FILENO, "oups\n", 5);
	else
	{
		write(STDOUT_FILENO, "YAYA\n", 5);
		elem = cmd->head;
		i = 0;
		while (elem != NULL)
		{
			/*
			if (ft_is_builtin(cmd_tab[0]) == 1)
				ft_serve_builtin(cmd_tab, cmd);
			*/
			ft_printf("cmd n%02d is is %s\n", i, elem->cmd);

			cmd_tab = ft_cmdsplit(elem->cmd);
			ft_printf("cmd_tab first elem is %s\n", cmd_tab[0]);
			elem = elem->next;
			i++;
		}
	}
	ft_reset_cmd(cmd);
	return (0);
}