#include "minishell.h"
#include "libft/libft.h"
#include <stddef.h>

 // if faut changer l'etat du flag input dans cette fonction.
static int	ft_add_end_quote(char *line, ptrdiff_t n, t_input *input)
{
	t_linput		*last;

	last = input->end;
	last->str = ft_strjoinfree(last->str, ft_strndup(line, n), LEFT | RIGHT);
	if (last->str == NULL)
		return (-1);
	input->end = last;
	input->flag ^= QUOTE + (input->flag & DQUOT ? DQUOT : SQUOT);
	return (1);
}

static int	ft_add_to_previous_line(char *line, t_input *input)
{
	char	*str;

	if (!(str = ft_strjoinfree(ft_strdup(line), "\n", LEFT)))
		return (-1);
	return (ft_add_linput(str, input, LAST));
}

static int	ft_add_quote(char *line, t_input *input, char c)
{
	char	*pos;
	char	*str;

	pos = ft_strchr(line + 1, c);
	if (pos == NULL)
	{
		input->flag |= QUOTE + (c == '"' ? DQUOT : SQUOT);
		str = ft_strjoinfree(ft_strdup(line), "\n", LEFT);
	}
	else
		str = ft_strndup(line, pos - line + 1);
	if (str == NULL || (ft_add_linput(str, input, NEW | QUOTE) == -1))
		return (-1);
	return (pos == NULL ? 1 : ft_search_opening_quote(pos + 1, input));	
}

static int	ft_add_start_line(char *line, ptrdiff_t n, t_input *input)
{
	char	*str;

	if (!(str = ft_strndup(line, n)))
		return (-1);
	return (ft_add_linput(str, input, NEW));
}

int	ft_search_opening_quote(char *line, t_input *input)
{
	char	*pos;
	char	*str;

	if (*line == '\0')
		return (1);
	pos = ft_strchrstr(line, "'\"");
	if (pos == NULL)
	{
		if (!(str = ft_strdup(line)))
			return (-1);
		return (ft_add_linput(str, input, NEW));
	}
	else 
	{
		if (!(ft_add_start_line(line, pos - line, input)) ||
			!(ft_add_quote(pos, input, *pos)))
			return (-1);
	}
	return (1);
}

int	ft_search_closing_quote(char *line, t_input *input)
{
	char	c;
	char	*pos;

	c = input->flag & SQUOT ? 39 : '"';
	if (!(pos = ft_strchr(line, c)))
	{
		if (!(ft_add_to_previous_line(line, input)))
			return (-1);
		return (0);
	}
	if (ft_add_end_quote(line, pos - line + 1, input) == 0 ||
		ft_search_opening_quote(pos + 1, input) == 0)
		return (-1);
	return (1);
}