#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "libft/incl/libft.h"
#include "libft/incl/ft_printf.h"
#include "libft/incl/get_next_line.h"
#include "minishell.h"

int			main(int ac, char **av, char **envp)
{
	char	*line;
	t_gcmd	cmd;

	line = NULL;
	cmd.flag = 0;
	cmd.head = NULL;
	cmd.end = NULL;
	cmd.rst = NULL;
	cmd.envp = envp;
	if (ac != 1)
	{
		printf("%s\n", av[1]);
		return (1);
	}
	write(STDOUT_FILENO, "$>", 2);
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
			write(STDOUT_FILENO,"$>",2);
		}
		else if (cmd.flag & DQUOT)
			write(STDOUT_FILENO,"dquote>", 7);
		else
			write(STDOUT_FILENO,"quote>", 6);
		free(line);
	}
	return (0);
}
