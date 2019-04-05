#include "minishell.h"
#include "libft/libft.h"
#include <stddef.h>

 // if faut changer l'etat du flag cmd dans cette fonction.
static int	ft_add_end_quote(char *line, ptrdiff_t n, t_cmd *cmd)
{
	t_lcmd		*last;

	last = cmd->end;
	last->str = ft_strjoinfree(last->str, ft_strndup(line, n), LEFT | RIGHT);
	if (last->str == NULL)
		return (0);
	cmd->end = last;
	cmd->flag ^= QUOTE + (cmd->flag & DQUOT ? DQUOT : SQUOT);
	return (1);
}

static int	ft_add_rest_line(char *line, t_cmd *cmd)
{
	char	*str;

	if (!(str = ft_strdup(line)))
		return (-1);
	return (ft_add_lcmd(str, cmd, LAST));
}

static int	ft_add_quote(char *line, t_cmd *cmd, char c)
{
	char	*pos;
	char	*str;

	pos = ft_strchr(line, c);
	if (pos == NULL)
	{
		cmd->flag |= QUOTE + (c == '"' ? DQUOT : SQUOT);
		str = ft_strdup(line);
	}
	else
		str = ft_strndup(line, line - pos);
	if (str == NULL || !(ft_add_lcmd(line, cmd, NEW | QUOTE)))
		return (-1);
	return (pos == NULL ? 1 : ft_search_opening_quote(pos + 1, cmd));	
}

static int	ft_add_start_line(char *line, ptrdiff_t n, t_cmd *cmd)
{
	char	*str;

	if (!(str = ft_strndup(line, n)))
		return (-1);
	return (ft_add_lcmd(line, cmd, NEW));
}

int	ft_search_opening_quote(char *line, t_cmd *cmd)
{
	int		i;
	char	*pos;

	pos = ft_strchrstr(line, "'\"");
	if (pos == NULL)
		if (!(ft_add_rest_line(line, cmd)))
			return (-1);
	else 
	{
		cmd->flag |= QUOTE + (*pos == '"' ? DQUOT : SQUOT);
		if (!(ft_add_start_line(line, line - pos , cmd)) ||
			!(ft_add_quote(pos + 1, cmd, *pos)))
			return (-1);
	}
	return (1);
}

int	ft_search_closing_quote(char *line, t_cmd *cmd)
{
	char	c;
	char	*pos;

	c = cmd->flag & SQUOT ? 39 : '"';
	if (!(pos = ft_strchr(line, c)))
		return (0);
	if (ft_add_end_quote(line, line - pos, cmd) == 0 ||
		ft_search_opening_quote(pos + 1, cmd) == 0)
		return (-1);
	return (1);
}