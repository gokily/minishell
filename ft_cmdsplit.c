/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gly <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 17:31:41 by gly               #+#    #+#             */
/*   Updated: 2019/02/22 09:24:33 by gly              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft/incl/libft.h"
#include "minishell.h"

#include "libft/incl/ft_printf.h"

static int		ft_count_word(const char *s)
{
	size_t	nb;
	size_t	i;
	int		flag;

	nb = 0;
	i = 0;
	flag = 0;
	while (s[i] != '\0')
	{
		if (s[i] == 34 && !(flag & SQUOT))
		{
			flag ^= DQUOT;
			flag ^= QUOTE;
		}
		else if (s[i] == 39 && !(flag & DQUOT))
		{
			flag ^= SQUOT;
			flag ^= QUOTE;
		}
		if (s[i] != ' ' && (s[i + 1] == ' ' || s[i + 1] == '\0')
			&& !(flag & QUOTE))
			nb++;
		i++;
	}
	ft_printf("There are %d words\n", nb);
	return (nb);
}

size_t			ft_elem_length(const char *s)
{
	size_t	i;
	int		flag;
	char	c;

	i = 0;
	flag = 0;
	c = 0;
	while (*s != '\0')
	{
		if (*s == ' ' && flag == 0)
			return (i);
		if ((*s == 34 || *s == 39) && (flag == 0 || *s == c))
		{
			flag = !flag;
			c = c == 0 ? *s : 0;
		}
		else
			i++;
		s++;
	}
	return (i);
}

size_t			ft_fill_tab_elem(char *elem, const char *s, size_t i)
{
	size_t		j;
	char		c;
	int			flag;

	j = 0;
	flag = 0;
	c = 0;
	elem[i] = '\0';
	while (i != 0)
	{
		if ((*s == 34 || *s == 39) && (flag == 0 || *s == c))
		{
			flag = !flag;
			c = c == 0 ? *s : 0;
		}
		else{
			*elem = *s;
			i--;
			elem++;
		}
		s++;
		j++;
	}
	return (j + (flag ? 1 : 0));
}

char			**ft_cmdsplit(const char *s)
{
	size_t	n;
	char	**tab;
	size_t	i;
	size_t	j;

	if (s == 0)
		return (0);
	if (!(tab = malloc(sizeof(*tab) * (ft_count_word(s) + 1))))
		return (0);
	n = 0;
	while (*s != '\0')
	{
		while (*s == ' ')
			s++;
		i = ft_elem_length(s);
		if (!(tab[n] = malloc(sizeof(char) * (i + 1))))
			return (NULL);
		j = ft_fill_tab_elem(tab[n], s, i);
		ft_printf("the n%02d element is %i character long and is |%s|, it was written in %d characters\n", n, i, tab[n], j);
		n++;
		s += j;
		ft_printf("s is at |%s|\n", s);
	}
	tab[n] = 0;
	return (tab);
}
