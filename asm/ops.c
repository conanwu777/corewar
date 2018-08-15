/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgleason <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/08 16:49:38 by cgleason          #+#    #+#             */
/*   Updated: 2018/08/08 16:49:41 by cgleason         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"

t_op	g_op_tab[17] =
{
	{"add", 4, 1, 3, {T_REG, T_REG, T_REG}, 0},
	{"sub", 5, 1, 3, {T_REG, T_REG, T_REG}, 0},
	{"and", 6, 1, 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 0},
	{"or", 7, 1, 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 0},
	{"xor", 8, 1, 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 0},
	{"ld", 2, 1, 2, {T_DIR | T_IND, T_REG}, 0},
	{"lld", 13, 1, 2, {T_DIR | T_IND, T_REG}, 0},
	{"ldi", 10, 1, 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 1},
	{"lldi", 14, 1, 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 1},
	{"fork", 12, 0, 1, {T_DIR}, 1},
	{"lfork", 15, 0, 1, {T_DIR}, 1},
	{"st", 3, 1, 2, {T_REG, T_IND | T_REG}, 0},
	{"sti", 11, 1, 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 1},
	{"live", 1, 0, 1, {T_DIR}, 0},
	{"zjmp", 9, 0, 1, {T_DIR}, 1},
	{"aff", 16, 1, 1, {T_REG}, 0},
	{NULL, 0, 0, 1, {0}, 0}
};

int		start_conversion(char *name, char *input, char ***tab,\
								t_nums *n)
{
	while (g_op_tab[++(n->i)].opcode)
		if (!ft_strcmp(name, g_op_tab[n->i].opcode))
			break ;
	if (!g_op_tab[n->i].opcode)
		free_and_clear(einvcom);
	put_bytes(&g_op_tab[n->i].byte, 1);
	*tab = ft_strsplit(input, ',');
	if (g_op_tab[n->i].coding_byte)
	{
		n->c = coding_byte(*tab);
		put_bytes(&(n->c), 1);
	}
	check_type(*tab, g_op_tab[n->i].input, g_op_tab[n->i].input_len);
	n->j = -1;
	return (0);
}

int		convert_loop1(char **tab, unsigned char **t, t_nums *n)
{
	if ((tab[n->j][0] == DIRECT_CHAR &&
	(g_op_tab[n->i].input[n->j] & T_DIR) != 0 && g_op_tab[n->i].dir_two) ||
	((ft_isdigit(tab[n->j][0]) || tab[n->j][0] == ':' || tab[n->j][0] == '-')
	&& (g_op_tab[n->i].input[n->j] & T_IND) != 0))
	{
		if (tab[n->j][0] == ':' ||
		(tab[n->j][0] == DIRECT_CHAR && tab[n->j][1] == ':'))
		{
			tab[n->j][0] == ':' ? add_label(&tab[n->j][1], 2) :
			add_label(&tab[n->j][2], 2);
			g_count += 2;
			return (1);
		}
		if (!is_number(tab[n->j] + (tab[n->j][0] == DIRECT_CHAR)))
			free_and_clear(einvnum);
		n->tmp = ft_atoi(tab[n->j] + (tab[n->j][0] == DIRECT_CHAR));
		*t = (unsigned char*)(&(n->tmp));
		n->k = 2;
		while (--(n->k) >= 0)
			put_bytes(&(*t)[n->k], 1);
	}
	return (0);
}

void	convert_loop2(char **tab, unsigned char **t, t_nums *n)
{
	if (tab[n->j][0] == DIRECT_CHAR &&
	(g_op_tab[n->i].input[n->j] & T_DIR) != 0 && !(g_op_tab[n->i].dir_two))
	{
		if (tab[n->j][0] == DIRECT_CHAR && tab[n->j][1] == ':')
		{
			add_label(&tab[n->j][2], 4);
			g_count += 4;
			return ;
		}
		if (!is_number(&tab[n->j][1]))
			free_and_clear(einvnum);
		n->tmp = ft_atoi(&tab[n->j][1]);
		*t = (unsigned char *)(&(n->tmp));
		n->k = 4;
		while (--(n->k) >= 0)
			put_bytes(&(*t)[n->k], 1);
	}
}

int		convert(char *name, char *input)
{
	t_nums			n;
	char			**tab;
	unsigned char	*t;

	n.i = -1;
	if (start_conversion(name, input, &tab, &n))
		return (-1);
	while (tab[++(n.j)])
	{
		if (tab[n.j][0] == 'r')
		{
			n.c = (unsigned char)ft_atoi(&tab[n.j][1]);
			put_bytes(&(n.c), 1);
		}
		convert_loop1(tab, &t, &n);
		convert_loop2(tab, &t, &n);
	}
	return (1);
}
