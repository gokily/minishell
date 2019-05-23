#include <unistd.h>
#include "ft_printf.h"
#include "minishell.h"

int		ft_error(char *filename, int err_no)
{
	static const char	*error[] = {"permission denied",
		"no such file or directory", "command not found"};
	ft_dprintf(STDERR_FILENO, "minishell: %s: %s\n", error[err_no], filename);
	return (1);
}
