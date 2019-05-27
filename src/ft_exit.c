#include "minishell.h"

int		ft_exit(char **arg, t_gcmd *cmd)
{
	if (*arg == NULL)
		exit(0);
	else if (arg[1] != NULL)
		ft_error(aewr);
	else
		exit(exit((unsigned char)ft_atoi(arg[0]));
	return (0);
}