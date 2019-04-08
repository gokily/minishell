#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "libft/libft.h"
#include "libft/get_next_line.h"
#include "minishell.h"

/*
int		ft_do_cmd(void)
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


static int	ft_parse_quote(char *line, t_cmd *cmd)
{
	int		i;

	i = 0;
	if (cmd->flag & QUOTE)
	{
		puts("searching closing quote");
		//on va peut etre devoir changer i en int pour le cas ou ya pas de quote fermant dans la line.
		i = ft_search_closing_quote(line, cmd);
	}
	else
	{
		i = ft_search_opening_quote(line, cmd);
	}
	return (i);
}

int			main(int ac, char **av, char **envp)
{
	char	*line;
	int		ret;
	t_cmd	cmd;

	line = NULL;
	
	cmd.flag = 0;
	cmd.head = NULL;
	cmd.end = NULL;
	cmd.envp = envp;
	
	ret = 0;
	if (ac != 1)
	{
		printf("%s\n", av[1]);
		return (1);
	}
	while (get_next_line(STDIN_FILENO, &line) == 1)
	{
		ret = ft_parse_quote(line, &cmd);
		printf("ret is %d\n", ret);
		free(line);
	}
	print_cmd(cmd);
	return (0);
}
