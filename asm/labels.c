/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   labels.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgleason <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/14 16:56:40 by cgleason          #+#    #+#             */
/*   Updated: 2018/08/14 16:56:56 by cgleason         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"

void	help_with_label(char *line, int i, t_lbl *tmp, t_lbl *lbl)
{
	char	*new;

	new = ft_strsub(line, 0, i);
	check_label_name(new);
	tmp = g_labels;
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, new))
		{
			tmp->found = true;
			tmp->loc = (short)g_count;
			free(new);
			break ;
		}
		tmp = tmp->nx;
	}
	if (tmp)
		return ;
	lbl = (t_lbl *)ft_memalloc(sizeof(t_lbl));
	lbl->name = new;
	lbl->loc = g_count;
	lbl->found = true;
	lbl->nx = g_labels;
	g_labels = lbl;
}

void	check_for_label(char **line)
{
	int		i;
	bool	label;
	char	*new;

	i = 0;
	label = false;
	new = NULL;
	while (line[0][i] && line[0][i] != ' ' && line[0][i] != '\t')
	{
		if (line[0][i] == ':' && (!line[0][i + 1] ||
			line[0][i + 1] == ' ' || line[0][i + 1] == '\t'))
		{
			help_with_label(*line, i, NULL, NULL);
			label = true;
		}
		i++;
	}
	if (!label)
		return ;
	if ((*line)[i])
		new = ft_strsub(*line, i + 1, ft_strlen(*line) - i - 1);
	free(*line);
	*line = new;
}

void	new_label(char *name, int bts)
{
	t_lbl		*lbl;

	lbl = (t_lbl*)malloc(sizeof(t_lbl));
	lbl->name = ft_strnew(ft_strlen(name));
	ft_strcpy(lbl->name, name);
	lbl->outputs = (t_output*)malloc(sizeof(t_output));
	lbl->outputs->addr = g_count;
	lbl->outputs->laddr = g_countl;
	lbl->outputs->bytes = bts;
	lbl->nout = 1;
	lbl->found = false;
	lbl->nx = g_labels;
	g_labels = lbl;
}

void	add_label(char *name, int bts)
{
	t_lbl		*tmp;
	t_output	*t;
	int			i;

	tmp = g_labels;
	while (tmp)
	{
		if (ft_strequ(tmp->name, name))
		{
			t = tmp->outputs;
			tmp->outputs = (t_output *)malloc(sizeof(*t) * (tmp->nout + 1));
			i = -1;
			while (++i < tmp->nout)
				tmp->outputs[i] = t[i];
			tmp->outputs[tmp->nout].addr = g_count;
			tmp->outputs[tmp->nout].laddr = g_countl;
			tmp->outputs[tmp->nout].bytes = bts;
			tmp->nout++;
			return ;
		}
		tmp = tmp->nx;
	}
	new_label(name, bts);
}

void	incert_labels(void)
{
	int				i;
	unsigned int	s;

	while (g_labels)
	{
		if (!g_labels->found)
			free_and_clear(eundlbl);
		i = -1;
		while (++i < g_labels->nout)
		{
			g_count = g_labels->outputs[i].addr;
			s = (unsigned int)(g_labels->loc - g_labels->outputs[i].laddr);
			put_bytes((unsigned char*)(&s), g_labels->outputs[i].bytes);
		}
		g_labels = g_labels->nx;
	}
	g_count = PROG_NAME_LENGTH;
	s = 0;
	put_bytes((unsigned char*)(&s), 4);
	put_bytes((unsigned char*)(&s), 4);
	s = (unsigned int)(g_header.prog_size);
	put_bytes((unsigned char*)(&s), 4);
}
