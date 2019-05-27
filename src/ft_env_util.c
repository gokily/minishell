#include <stdlib.h>
#include "libft.h"
#include "minishell.h"

int     ft_del_envvar(char *var, char **envp)
{
	size_t	i;

	i = 0;
	if (envp == NULL)
		return (0);
	while (envp[i] != NULL)
	{
		if (ft_strcmp(var, envp[i]) == 0)
		{
			while (envp[i + 1] != NULL)
			{
				envp[i] = envp[i + 1];
				i++;
			}
			envp[i] = NULL;
			return (0);
		}
		i++;
	}
	return (0);
}

static inline char	**ft_add_var2envp(char *var, char **envp)
{
	size_t	i;
	size_t	j;
	char	**tab;

	i = 0;
	j = 0;
	while (envp[i] != NULL)
		i++;
	i++;
	if (!(tab = malloc(sizeof(char *) * (i + 1))))
		return (NULL);
	tab[i] = NULL;
	while (j != i)
	{
		tab[j] = envp[j];
		j++;
	}
	tab[j] = var;
	return (tab);
}

static inline int	ft_find_var(char **envp, char *var, size_t i)
{
	int		j;

	j = 0;
	while (envp[j] != NULL)
	{
		if (ft_strncmp(envp[j], var, i) == 0)
			return (j);
		j++;
	}
	return (-1);
}

char	**ft_add_envvar(char *var, char **envp)
{
	size_t	i;
	int		j;

	if (envp == NULL)
		return (ft_add_var2envp(var, envp));
	i = 0;
	while (var[i] != '=')
		i++;
	if (envp == NULL && (j = ft_find_var(envp, var, i) != -1))
		envp[j] = var;
	else
		return (ft_add_var2envp(var, envp));
	return (envp);
}