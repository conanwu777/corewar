/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgleason <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/08 17:01:30 by cgleason          #+#    #+#             */
/*   Updated: 2018/08/08 17:01:31 by cgleason         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"

t_lbl	*g_labels = NULL;

char	*g_errors[14] = {
	"Usage: asm champion.s",
	"Invalid input file",
	"Insufficient memory",
	"Label uses invalid character",
	"The champion does not have a comment",
	"Champion comment is too long",
	"The champion does not have a name",
	"Champion name is too long",
	"Label was never declared",
	"Too many parameters",
	"Invalid parameters",
	"Too few parameters",
	"Invalid command",
	"Invalid number"
};

void	free_lbls(void)
{
	t_lbl	*tmp;

	if (g_labels == NULL)
		return ;
	while (g_labels)
	{
		tmp = g_labels;
		g_labels = g_labels->nx;
		free(tmp->name);
		free(tmp);
	}
}

void	free_and_clear(t_err_msg ind)
{
	if (ind <= eusage)
		ft_printf("{Y}%s\n", g_errors[ind]);
	else if (ind == einvalid)
		ft_printf("{R}%s\n", g_errors[ind]);
	else if (ind <= eundlbl)
		ft_printf("{O}%s\n", g_errors[ind]);
	else
		ft_printf("{O}line %d : %s\n", g_line, g_errors[ind]);
	free_lbls();
	exit(-1);
}

int		find_command(char *line)
{
	char	*new;
	char	*command;
	int		i;
	int		num;

	if (line[0] == '\0')
		return (0);
	str_trim(&line);
	check_for_label(&line);
	if (line == NULL)
		return (0);
	i = 0;
	while (line[i] && line[i] != ' ')
		i++;
	command = ft_strsub(line, 0, i);
	line = cw_strchop(line, i);
	new = ft_strnew(ft_strlen(line) + 1);
	i = -1;
	num = 0;
	while (line[++i])
		if (line[i] != ' ' && line[i] != '\t')
			new[num++] = line[i];
	free(line);
	line = new;
	return (command[0] == '\0') ? (0) : (convert(command, line));
}

void	final_output(char *str)
{
	char	*file;

	g_header.prog_size = g_count - HEADER_LENGTH;
	incert_labels();
	file = ft_strsub(str, 0, ft_strlen(str) - 2);
	ft_printf("{G}Succesfully wrote to %s.cor!\n", file);
	file = cw_stradd(file, ".cor", 4);
	remove(file);
	g_out = open(file, O_CREAT | O_WRONLY, 0777);
	write(g_out, g_buf, g_header.prog_size + HEADER_LENGTH);
	close(g_out);
	close(g_rd);
}

int		main(int ac, char **av)
{
	char	*line;

	g_line = 3;
	ft_bzero((void *)g_buf, CHAMP_LENGTH);
	g_header.magic = COREWAR_EXEC_MAGIC;
	line = NULL;
	if ((ac != 2) || (g_rd = open(av[1], O_RDONLY)) < 0)
		(ac != 2) ? free_and_clear(eusage) : free_and_clear(einvalid);
	if (!get_name_comment(g_rd, 0) || !get_name_comment(g_rd, 1))
		return (0);
	put_bytes((unsigned char *)(&g_header.magic), 4);
	add_field(g_name, PROG_NAME_LENGTH);
	g_count += 8;
	add_field(g_comment, COMMENT_LENGTH + 4);
	while (ft_gnl(g_rd, &line))
	{
		g_countl = g_count;
		remove_comments(&line);
		if (find_command(line) == -1)
			return (0);
		g_line++;
	}
	final_output(av[1]);
	return (0);
}
