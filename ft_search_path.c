
#include <dirent.h>
#include "libft/incl/libft.h"
#include "minishell.h"

static inline int	ft_exec_exist_in_path(char *filename, char *pathname)
{
	DIR				*dir;
	struct dirent	*elem;

	if (!(dir = opendir(pathname)))
		return (-1);
	while ((elem = readdir(dir)))
	{
		if (ft_strcmp(elem->d_name, filename) == 0)
		{
			closedir(dir);
			return (1);
		}
	}
	closedir(dir);
	return (0);
}

static inline char	**ft_create_path_tab(char **envp)
{
	char	**path;
	size_t	i;

	i = 0;
	path = NULL;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			if ((path = ft_strsplit((envp[i]) + 5, ':')) == NULL)
				return (NULL);
			return (path);
		}
		i++;
	}
	return (NULL);
}

int		ft_search_path(char *exec_name, char **path, char **envp)
{
	char	**path_tab;
	size_t	i;

	i = 0;
	if ((path_tab = ft_create_path_tab(envp)) == NULL)
		return (-1);
	while (path_tab[i] != NULL)
	{
		if (ft_exec_exist_in_path(exec_name, path_tab[i]) == 1)
		{
			*path = path_tab[i];
			return (0);
		}
		i++;
	}
	ft_error(exec_name, NOCMD);
	return (0);
}