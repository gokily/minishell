
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "libft/incl/libft.h"
#include "minishell.h"


static inline int	ft_exec_cmd(char *cmd, char **arg_tab, char **envp)
{
	pid_t	pid;
	pid_t	wpid;
	int		status;

	status = 0;
	pid = fork();
	if (pid == 0)
		execve(cmd, arg_tab, envp);
	wpid = waitpid(pid, &status, WUNTRACED);
	if (wpid == -1)
		write(STDOUT_FILENO, "WPID ERROR\n", 11);
	return (status);
}

static inline int		ft_is_executable(char *filepath)
{
	struct stat	statbuf;

	if (lstat(filepath, &statbuf) == -1)
		ft_error(filepath, NOFILE);
	else if (statbuf.st_mode & S_IXUSR)
		return (1);
	else
		ft_error(filepath, PERMDEN);
	return (0);
}

int		ft_exec_cmd_direct(char **cmd_tab, char **envp)
{
	if (ft_is_executable(cmd_tab[0]))
		ft_exec_cmd(cmd_tab[0], cmd_tab, envp);
	return (1);
}

int		ft_exec_cmd_from_path(char **cmd_tab, char *path, char **envp)
{
	char *filepath;

	if (!(filepath = ft_strjoin_three(path, "/", cmd_tab[0])))
		return (-1);
	if (ft_is_executable(filepath))
		ft_exec_cmd(filepath, cmd_tab, envp);
	else
		ft_error(filepath, PERMDEN);
	return (0);
}