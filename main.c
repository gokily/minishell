#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "libft/incl/libft.h"
#include "libft/incl/get_next_line.h"
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

/*
static int	ft_parse_semicol(t_linput *linput, t_cmd *cmd)
{
	char	*pos;

	if ((pos = ft_strchr(linput->str, ';')))
	{
			if (cmd->flag & SEMICOL)
			{
				//treat the double ; error
				return (0);
			}
	}
	else
	{
		if (!(ft_fill_cmd(linput->str, cmd)))
			return (0);
	}
}

static int	ft_parse_input(t_input *input, t_cmd *cmd)
{
	t_linput	*linput;
	t_cmd		*cmd;

	if (!(cmd = ft_cmd_new()))
		return (0);
	linput = input->head;
	while (linput != NULL)
	{
		ft_add_lcmd(cmd, linput);
		linput = linput->next;
	}
	return (1);
}

static int	ft_parse_quote(char *line, t_input *input)
{
	int		i;

	i = 0;
	if (input->flag & QUOTE)
		i = ft_search_closing_quote(line, input);
	else
		i = ft_search_opening_quote(line, input);
	return (i);
}
 */

int			main(int ac, char **av, char **envp)
{
	char	*line;
	t_gcmd	cmd;

	line = NULL;
	cmd.flag = 0;
	cmd.head = NULL;
	cmd.end = NULL;
	cmd.envp = envp;
	if (ac != 1)
	{
		printf("%s\n", av[1]);
		return (1);
	}
	write(STDOUT_FILENO, "$>", 3);
	while (get_next_line(STDIN_FILENO, &line) == 1)
	{
		if ((ft_parse_line(line, &cmd)) == -1)
		{
			//free all
			return (1);
		}
		if (!(cmd.flag & QUOTE))
		{
			if (ft_do_cmd(&cmd) == -1)
				return (1);
			write(STDOUT_FILENO,"$>",3);
		}
		else if (cmd.flag & DQUOT)
			write(STDOUT_FILENO,"dquote>", 8);
		else
			write(STDOUT_FILENO,"quote>", 7);
		free(line);
	}
	return (0);
}
