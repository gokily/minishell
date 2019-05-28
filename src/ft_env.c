/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gly <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 10:55:09 by gly               #+#    #+#             */
/*   Updated: 2019/05/27 11:20:27 by gly              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/wait.h>
#include "libft.h"
#include "ft_printf.h"
#include "minishell.h"
#include "ft_env.h"

static inline int	ft_check_u(char **arg, size_t *i, t_gcmd *cmd, size_t j)
{
	if (arg[*i][j] == '\0')
	{
		cmd->envp = ft_del_envvar(arg[*i + 1], cmd->envp);
		(*i)++;
	}
	else
		cmd->envp = ft_del_envvar(arg[*i] + j, cmd->envp);
	return (0);
}

static inline int	ft_check_flag2(char **arg, size_t *i, t_gcmd *cmd,
		size_t j)
{
	int		status;

	status = 0;
	if (arg[*i][j] == 'i')
	{
		cmd->envp = NULL;
		status = ft_check_flag2(arg, i, cmd, j + 1);
	}
	else if (arg[*i][j] == 'u')
		status = ft_check_u(arg, i, cmd, j + 1);
	else
		ft_printf("env: illegal option -- %c\nusage: env [-i] [-u name]\n\
			[name=value ...] [utility [argument ...]]\n", arg[*i][j]);
	return (status);
}

static inline int	ft_check_flag(char **arg, size_t *i, t_gcmd *cmd)
{
	int		status;

	status = 0;
	while (arg[*i] != NULL)
	{	
		if (arg[*i][0] == '-')
			status = ft_check_flag2(arg, i, cmd, 1);
		(*i)++;
	}
	return (status);
}

static inline int	ft_check_var(char **arg, size_t *i, t_gcmd *cmd)
{
	if (arg[*i] == NULL)
		return (0);
	while (arg[*i] != NULL && ft_strchr(arg[*i], '='))
	{
		if (!(cmd->envp = ft_add_envvar(arg[*i], cmd->envp)))
			return (-1);
		(*i)++;
	}
	return (0);
}

int					ft_env(char **arg, t_gcmd *cmd)
{
	size_t	i;
	pid_t	pid;
	pid_t	wpid;
	int		status;

	status = 0;
	pid = fork();
	if (pid == 0)
	{
		i = 0;
		if (cmd->path != NULL)
			status = ft_create_path_tab(cmd->envp, &(cmd->path));
		if (status == -1) // comment faire sortir du programme et pas seulement du fork ?
			return (-1);
		ft_check_flag(arg, &i, cmd);
		if (ft_check_var(arg, &i, cmd) == -1)
			return (-1);
		ft_do_cmd(cmd); // il faut changer ce truc
		return (0);
	}
	wpid = waitpid(pid, &status, WUNTRACED);
	if (wpid == -1)
		write(STDOUT_FILENO, "WPID ERROR\n", 11);
	return (status);
}