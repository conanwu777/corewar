/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   name_comments.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgleason <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/14 16:59:18 by cgleason          #+#    #+#             */
/*   Updated: 2018/08/14 16:59:28 by cgleason         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"

void	add_field(unsigned char *field, int size)
{
	int		i;
	bool	end;

	i = 0;
	end = false;
	while (i < size)
	{
		if (!end && (!field || !field[i]))
			end = true;
		if (end == false)
			put_bytes(&field[i], 1);
		else
			g_buf[g_count++] = 0;
		i++;
	}
}

int		no_name_comment(bool c, char *line)
{
	free(line);
	if (c)
		free_and_clear(enocomment);
	else
		free_and_clear(enoname);
	return (-1);
}

int		get_name_comment(int fd, bool c)
{
	char	*tag;
	char	*line;
	int		i;

	ft_gnl(fd, &line);
	if (line == NULL)
		return (no_name_comment(c, line));
	str_trim(&line);
	i = 0;
	while (line[i] && line[i] != ' ')
		i++;
	tag = ft_strsub(line, 0, i);
	line = cw_strchop(line, i);
	if ((c == 0 && ft_strcmp(tag, ".name")) ||
			(c == 1 && ft_strcmp(tag, ".comment")))
		return (no_name_comment(c, line));
	if (c == 0)
		g_name = (unsigned char*)ft_strsub(line, 2, ft_strlen(line) - 3);
	if (c == 0 && ft_strlen((char *)g_name) > PROG_NAME_LENGTH)
		free_and_clear(elgname);
	if (c == 1)
		g_comment = (unsigned char*)ft_strsub(line, 2, ft_strlen(line) - 3);
	if (c == 1 && ft_strlen((char *)g_comment) > COMMENT_LENGTH)
		free_and_clear(elgname);
	return (1);
}

void	remove_comments(char **line)
{
	int		i;
	char	*tmp;

	i = 0;
	while ((*line)[i])
	{
		if ((*line)[i] == '#')
		{
			tmp = ft_strsub(*line, 0, i);
			free(*line);
			*line = tmp;
		}
		i++;
	}
}

void	check_label_name(char *name)
{
	int		i;
	int		j;
	bool	b;

	if (!name)
		free_and_clear(enomem);
	i = 0;
	while (name[i])
	{
		j = -1;
		b = false;
		while (LABEL_CHARS[++j] && !b)
			if (name[i] == LABEL_CHARS[j])
				b = true;
		if (!b)
			free_and_clear(einvlbl);
		i++;
	}
}
