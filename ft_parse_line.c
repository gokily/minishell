#include <stdlib.h>
#include "libft/incl/libft.h"
#include "minishell.h"

#include "libft/incl/ft_printf.h"

static inline int	ft_add_rst(t_gcmd *cmd, char *line)
{
	if (cmd->rst != NULL)
		cmd->rst = ft_strjoinfree(cmd->rst, line, LEFT);
	else
		cmd->rst = ft_strdup(line);
	cmd->rst = ft_strjoinfree(cmd->rst, "\n", LEFT);
	if (cmd->rst == NULL)
		return (-1);
	return (1);
}

static inline int	ft_line_end(t_gcmd *cmd, char *line, size_t i)
{
	if (i != 0)
	{
		if (cmd->flag & QUOTE)
		{
			if (ft_add_rst(cmd, line) == -1)
				return (-1);
		}
		else if (ft_add_lcmd(cmd, line, i) == -1)
			return (-1);
	}
	return (0);
}

int		ft_parse_line(char *line, t_gcmd *cmd)
{
	size_t		i;

	i = 0;
	while (line[i] != '\0')
	{
		if (!(cmd->flag & QUOTE) && line[i] == ';')
		{
			if (ft_add_lcmd(cmd, line, i) == -1)
				return (-1);
			line += i + 1;
			i = 0;
		}
		else if (!(cmd->flag & QUOTE)
			&& line[i] == '\\' && ft_strchr(SHELLESC, line[i + 1]))
			i += 2;
		else 
		{	
			cmd->flag = ft_check_quote(line[i], cmd->flag);
			if ((cmd->flag & DQUOT) && line[i] == '\\'
				&& ft_strchr(DQUOTEESC, line[i + 1]))
				i++;
			i++;
		}
	}
	return (ft_line_end(cmd, line, i));
}