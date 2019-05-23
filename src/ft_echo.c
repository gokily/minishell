#include <unistd.h>
#include <stdlib.h>
#include "libft.h"
#include "minishell.h"

static inline int	ft_only_flag(char *option)
{
	size_t	i;

	i = 0;
	while (option[i] != '\0')
	{
		if (ft_strchr(ECHOFLAG, option[i]) == NULL)
			return (0);
		i++;
	}
	return (1);
}

static inline size_t	ft_check_flag(char **arg, int *flag)
{
	int		status;
	size_t	i;
	size_t	j;

	status = 0;
	i = 0;
	while (status != 1 && arg[i] != NULL)
	{	
		if (arg[i][0] == '-' && ft_only_flag(arg[i] + 1))
		{
			j = 1;
			while (arg[i][j] != '\0')
			{
				if (arg[i][j] == 'e')
					*flag |= ECHOE;
				else if (arg[i][j] == 'n')
					*flag |= ECHON;
				j++;
			}
			i++;
		}
		else
			status = 1;
	}
	return (i);
}

static inline	int	ft_echo_direct(char **str_tab)
{
	size_t	len;
	size_t	i;
	size_t	j;
	char	*str;

	len = 0;
	i = 0;
	while (str_tab[i] != NULL)
	{
		j = 0;
		while (str_tab[i][j] != '\0')
			j++;
		len += j + 1;
		i++;
	}
	if (!(str = malloc(sizeof(char) * len)))
		return (-1);
	i = 0;
	len = 0;
	while (str_tab[i] != NULL)
	{
		j = 0;
		while (str_tab[i][j] != '\0')
		{
			str[len] = str_tab[i][j];
			j++;
			len++;
		}
		str[len++] = ' ';
		i++;
	}
	str[len - 1] = '\0';
	write(STDOUT_FILENO, str, len - 1);
	return (0);
}

int		ft_echo(char **arg, t_gcmd *cmd)
{
	int		flag;
	size_t	i;
	int		ret;

	flag = 0;
	cmd->flag = 0; // a voir
	i = ft_check_flag(arg, &flag);
	if (flag & ECHOE)
		ret = ft_echo_interpret(arg + i);
	else
		ret = ft_echo_direct(arg + i);
	if (ret != 0)
		return (ret);
	if (!(flag & ECHON))
		write(STDOUT_FILENO, "\n", 1);
	return (0);
}