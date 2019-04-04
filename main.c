#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "libft/libft.h"
#include "libft/get_next_line.h"

int		main(int ac, char **av, char **envp)
{
	char	*line;
	char	**tab;
	pid_t	pid;
	pid_t	wpid;
	int		status;

	line = NULL;
	status = 0;
	if (ac != 1)
	{
		printf("%s\n", av[1]);
		return (1);
	}
	while (get_next_line(STDIN_FILENO, &line) == 1)
	{
		pid = fork();

		tab = ft_strsplit(line, ' ');
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

			free(line);
	}
	
	return (0);
}
