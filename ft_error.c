#include <unistd.h>
#include "libft/incl/ft_printf.h"
#include "minishell.h"

int		ft_error(char *filename, int err_no)
{
	static const char	*error[] = {"permission denied",
		"no such file or directory", "command not found"};

/*
	if (ft_strlen(file) == 0)
	{
		perror("ls: fts_open");
		free(ls);
		exit(EXIT_FAILURE);
	}

*/
	ft_dprintf(STDERR_FILENO, "minishell: %s: %s\n", error[err_no], filename);
	return (1);
}
