#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "libft/incl/libft.h"
#include "minishell.h"

static inline int		ft_cd_error(int i)
{
	if (i == 1)
	{
		write(STDERR_FILENO, "minishell: cd: too many arguments\n", 34);
		return (-1);
	}
	return (0);
}

static inline int		ft_check_path(char *filepath)
{
	struct stat	statbuf;

	if (lstat(filepath, &statbuf) == -1)
		ft_error(filepath, NOFILE);
	else if (S_ISDIR(statbuf.st_mode))
		return (1);
	else
		ft_error(filepath, PERMDEN);
	return (0);
}

static inline char		*ft_find_home_path(t_gcmd *cmd)
{
	size_t	i;

	i = 0;
	while (cmd->envp[i] != NULL)
	{
		if (ft_strncmp(cmd->envp[i], "HOME=", 5) == 0)
			return (ft_strdup(cmd->envp[i] + 5));
		i++;
	}
	write(STDERR_FILENO, "minishell: cd: HOME not set\n", 28);
	return (NULL); 
}

static inline int		ft_cd_home(t_gcmd *cmd)
{
	char	*homepath;
	
	homepath = ft_find_home_path(cmd);
	if (ft_check_path(homepath) == 0)
		return (-1);
	chdir(homepath);
	return (0);
}

int		ft_cd(char **arg, t_gcmd *cmd)
{
	char	*new;

	new = *arg;
	if (new == NULL)
		return (ft_cd_home(cmd));
	if (arg[1] != NULL)
		return (ft_cd_error(1));
	if (ft_check_path(new) == 0)
		return (-1);
	chdir(new);
	return (0);
}