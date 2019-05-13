#include <stdlib.h>
#include "libft/incl/libft.h"
#include "minishell.h"

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
		if (line[i] == ';' && !(cmd->flag & QUOTE))
		{
			if (ft_add_lcmd(cmd, line, i) == -1)
				return (-1);
			line += i + 1;
			i = 0;
		}
		else 
		{	
			if (line[i] == 34 && !(cmd->flag & SQUOT))
			{
				cmd->flag ^= DQUOT;
				cmd->flag ^= QUOTE;
			}
			else if (line[i] == 39 && !(cmd->flag & DQUOT))
			{
				cmd->flag ^= SQUOT;
				cmd->flag ^= QUOTE;
			}
			i++;
		}
	}
	return (ft_line_end(cmd, line, i));
}