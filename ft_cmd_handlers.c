#include "minishell.h"

static t_lcmd	*ft_lcmd_new(void)
{
	t_cmd	*lcmd;

	if (!(lcmd = malloc(sizeof(t_lcmd))))
		return (NULL);
	lcmd->n = 0;
	lcmd->head = NULL;
	lcmd->end = NULL;
	lcmd->next = NULL;
	return (lcmd);
}

static void	ft_lcmd_push(t_lcmd *elem, t_cmd *cmd)
{
	if (cmd->head == NULL)
	{
		cmd->head = elem;
		cmd->end = elem;
	}
	else
	{
		cmd->end->next = elem;
		cmd->end = elem;
	}
}

int		ft_add_lcmd(t_cmd *cmd, t_linput *linput)
{
	t_lcmd	*elem;

	if (cmd->flag & SEMICOL)
	{
		if (!(elem = ft_lcmd_new()))
			return (0);
		
	}
}


















/*
int	ft_add_quote_lcmd(t_linput *linput, t_cmd *cmd)
{
	t_lcmd	*elem;

	if (cmd->flag & SEMICOL || cmd->head == NULL)
	{
		if (!(elem = ft_lcmd_new()))
			return (0);
		if (!(elem->cmd = ft_strndup(linput->str + 1,
			ft_strlen(linput->str + 1) - 1)))
			return (0);
		ft_lcmd_push(elem, cmd);
		cmd->flag ^= SEMICOL;
	}
	else 
	{
		elem = cmd->end;
		if (elem->arg == NULL)
		{
			if (!(elem->arg = ft_strdup(linput->str)))
				return (0);
		}
		else if (!(elem->arg = ft_strjoinfree(elem->arg,
			ft_strdup(linput->str), LEFT | RIGHT)))
			return (0);
	}
	return (1);
}

int	ft_fill_cmd(char *str, t_cmd *cmd)
{
	t_lcmd	*elem;
	char	*pos;

	if (cmd->flag & SEMICOL || cmd->head == NULL)
	{
		if (!(elem = ft_lcmd_new()))
			return (0);
		pos = ft_strchr(str, ' ');
		n = pos == NULL ? ft_strlen(str) : pos - str;
		if (!(elem->cmd = ft_strndup(str, n)))
			return (0);
		ft_lcmd_push(elem, cmd);
		cmd->flag ^= SEMICOL;
	}
}*/