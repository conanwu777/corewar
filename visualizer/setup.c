/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/08 20:02:06 by cwu               #+#    #+#             */
/*   Updated: 2018/08/08 20:02:09 by cwu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "visual.h"

unsigned int	g_color[8];

void			init_variables(int ac, char **av)
{
	g_cur_cycle = 0;
	g_checks = 0;
	g_cycle_die = CYCLE_TO_DIE;
	g_processes = NULL;
	g_nproc = 0;
	g_pause = 0;
	g_step = 0;
	g_gameover = 0;
	g_dump_core = -1;
	g_pl = 4;
	g_pls = (t_player *)ft_memalloc(sizeof(t_player) * (g_pl + 1));
	g_visual = 1;
	g_total_cycle = 0;
	g_winner = NULL;
	pls_init(ac, av);
	set_start_color();
}

void			set_player_variables(int p, char *str, int pl_num)
{
	unsigned int i;

	g_pls[p].fd = open(str, O_RDONLY);
	g_pls[p].size = champ_size(g_pls[p].fd);
	lseek(g_pls[p].fd, 0, SEEK_SET);
	read(g_pls[p].fd, &i, 4);
	if (g_pls[p].fd == -1 || i != COREWAR_EXEC_MAGIC)
		clear_and_free(1);
	g_pls[p].name = ft_strnew(PROG_NAME_LENGTH);
	lseek(g_pls[p].fd, 4, SEEK_SET);
	read(g_pls[p].fd, g_pls[p].name, PROG_NAME_LENGTH);
	g_pls[p].comment = ft_strnew(COMMENT_LENGTH);
	lseek(g_pls[p].fd, PROG_NAME_LENGTH + 12, SEEK_SET);
	read(g_pls[p].fd, g_pls[p].comment, COMMENT_LENGTH);
	lseek(g_pls[p].fd, PROG_NAME_LENGTH + COMMENT_LENGTH + 16, SEEK_SET);
	g_pls[p].id = (pl_num) ? pl_num : p + 1;
	g_pls[p].lives = 0;
	g_pls[p].total_occupied = 0;
	g_pls[p].c1 = g_color[p];
	g_pls[p].c2 = g_color[p + 4];
	g_pl--;
}

void			pls_finish_init(void)
{
	int		p;
	int		i;
	t_byte	bt;

	g_pl = 4 - g_pl;
	p = -1;
	while (++p < g_pl)
	{
		i = p * MEM_SIZE / g_pl;
		start_process(i, &g_pls[p]);
		while (read(g_pls[p].fd, &bt, 1) == 1)
		{
			g_memory[i].c = bt;
			i++;
		}
	}
}

void			pls_init(int ac, char **av)
{
	int		p;
	int		i;
	int		pl_num;

	i = 0;
	p = 0;
	while (++i < ac && g_pl)
	{
		pl_num = 0;
		while (av[i][0] == '-')
		{
			i = execute_option(ac, av, i, &pl_num);
			if (i == 0)
				clear_and_free(2);
		}
		set_player_variables(p, av[i], pl_num);
		p++;
	}
	pls_finish_init();
}

void			set_start_color(void)
{
	int i;
	int p;

	i = -1;
	while (++i < MEM_SIZE)
	{
		p = -1;
		while (++p < g_pl)
			if (i >= p * MEM_SIZE / g_pl &&
				i < p * MEM_SIZE / g_pl + (int)g_pls[p].size)
			{
				g_memory[i].owner = &g_pls[p];
				g_pls[p].total_occupied++;
			}
		g_memory[i].change = 1;
	}
}
