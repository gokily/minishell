#include <unistd.h>
#include <stdlib.h>
#include "libft.h"
#include "minishell.h"

static inline size_t ft_interpret_len(char **str_tab)
{
	size_t	i;
	size_t	j;
	size_t	len;

	len = 0;
	i = 0;
	while (str_tab[i] != NULL)
	{
		j = 0;
		while (str_tab[i][j] != '\0')
		{
			if (str_tab[i][j] == '\\' && str_tab[i][j + 1] == 'c')
				return (len + 1);
			if (str_tab[i][j] == '\\' && ft_strchr(ECHOESC, str_tab[i][j + 1]))
				j++;
			len++;
			j++;
		}
		len++;
		i++;
	}
	return (len);
}

static inline char	ft_interpret_replace(char c)
{
	size_t				i;
	static const char	replaced[] = "\\abefnrtv";
	static const char	replacement[] = "\\\a\b\e\f\n\r\t\v";

	i = 0;
	while (replaced[i] != '\0')
	{
		if (c == replaced[i])
			return (replacement[i]);
		i++;
	}
	return (0);
}

static inline int	ft_fill_str(char *str, char **str_tab, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (str_tab[i] != NULL)
	{
		j = 0;
		while (str_tab[i][j] != '\0')
		{
			if (str_tab[i][j] == '\\' && str_tab[i][j + 1] == 'c')
				return (1);
			if (str_tab[i][j] == '\\' && ft_strchr(ECHOESC, str_tab[i][j + 1]))
			{
				str[len++] = ft_interpret_replace(str_tab[i][j + 1]);
				j++;
			}
			else
				str[len++] = str_tab[i][j];
			j++;
		}
		str[len++] = ' ';
		i++;
	}
	return (0);
}

int					ft_echo_interpret(char **str_tab)
{
	size_t	len;
	char	*str;
	int		ret;

	len = ft_interpret_len(str_tab);
	if (!(str = malloc(sizeof(char) * len)))
		return (-1);
	len = 0;
	ret = ft_fill_str(str, str_tab, len);
	str[len - 1] = '\0';
	write(STDOUT_FILENO, str, len - 1);
	return (ret);
}