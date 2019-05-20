#include "libft/incl/libft.h"
#include "minishell.h"
#include "builtin.h"


#include "libft/incl/ft_printf.h"

int		ft_find_builtin(char *cmd)
{
	int		i;

	i = 0;
	while (ft_strcmp(g_builtin_tab[i].name, "end") != 0)
	{
		if (ft_strcmp(cmd, g_builtin_tab[i].name) == 0)
			return (i);
		i++;
	}
	return (-1);
}

int		ft_serve_builtin(int i, char **cmd_tab, t_gcmd *cmd)
{
	int		status;

	if ((status = g_builtin_tab[i].f(cmd_tab + 1, cmd)) == -1)
		return (-1);
	return (status);
}