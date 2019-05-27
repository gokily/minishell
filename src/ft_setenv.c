#include "minishell.h"
#include "builtin.h"

int		ft_setenv(char **arg, t_gcmd *cmd)
{
	char *var;
	char *word;
	char *join;

	if (*arg == NULL)
		return (0);
	var = arg[0];
	word = arg[1];
	if (!(join = ft_strjoin_three(var, "=", word == NULL ? "", word)))
		return (-1);
	cmd->envp = ft_add_envvar(join, cmd->envp);
	return (cmd->envp == NULL ? -1 : 0);
}