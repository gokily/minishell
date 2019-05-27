#include "minishell.h"
#include "ft_env.h"

int		ft_unsetenv(char **arg, t_gcmd *cmd)
{
	size_t	i;

	i = 0;
	if (*arg == NULL)
		return (0);
	while (arg[i] != NULL)
	{
		cmd->envp = ft_del_envvar(arg[i], cmd->envp);
		i++;
	}
	return (0);
}