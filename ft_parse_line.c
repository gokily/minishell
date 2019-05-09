#include <stdlib.h>
#include "minishell.h"

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
		else if (line[i] == '"' && !(cmd->flag & SQUOT)
		{
			cmd->flag ^= DQUOT;
			cmd->flag ^= QUOTE;
		}
		else if (line[i] == 39 && !(cmd->flag & DQUOT)
		{
			cmd->flag ^= DQUOT;
			cmd->flag ^= QUOTE;
		}
		else
			i++;
	}
}