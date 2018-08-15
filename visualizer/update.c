/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/08 19:47:41 by cwu               #+#    #+#             */
/*   Updated: 2018/08/08 19:47:45 by cwu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

t_op			g_optab[17] =
{
	{"*", 10, &live_01, 0, 1, {T_DIR}, 0},
	{"l", 5, &ld_02, 1, 2, {T_DIR | T_IND, T_REG}, 0},
	{"s", 5, &st_03, 1, 2, {T_REG, T_IND | T_REG}, 0},
	{"+", 10, &add_04, 1, 3, {T_REG, T_REG, T_REG}, 0},
	{"-", 10, &sub_05, 1, 3, {T_REG, T_REG, T_REG}, 0},
	{"&", 6, &and_06, 1, 3,
		{T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 0},
	{"o", 6, &or_07, 1, 3,
		{T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 0},
	{"x", 6, &xor_08, 1, 3,
		{T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 0},
	{"J", 20, &zjmp_09, 0, 1, {T_DIR}, 1},
	{"L", 25, &ldi_10, 1, 3,
		{T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 1},
	{"S", 25, &sti_11, 1, 3,
		{T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 1},
	{"F", 800, &fork_12, 0, 1, {T_DIR}, 1},
	{">", 10, &lld_13, 1, 2, {T_DIR | T_IND, T_REG}, 0},
	{"=", 50, &lldi_14, 1, 3,
		{T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 1},
	{"Y", 1000, &lfork_15, 0, 1, {T_DIR}, 1},
	{"a", 2, &aff_16, 1, 1, {T_REG}, 0},
	{0, 0, 0, 0, 0, {0}, 0}
};

int		check_for_command(t_process *process)
{
	if (g_memory[process->pc].c >= 1 && g_memory[process->pc].c <= 16)
	{
		process->post_wait = &g_optab[g_memory[process->pc].c - 1];
		process->wait = process->post_wait->wait - 1;
	}
	else
	{
		process->post_wait = NULL;
		process->wait = 0;
	}
	return (0);
}

void	hexdumper(t_mem *memory)
{
	int	i;

	i = -1;
	while (++i < MEM_SIZE)
	{
		if (i != 0 && i % 32 == 0)
			ft_printf("\n");
		if (!(i % 32))
			ft_printf("%.8x ", i);
		if (memory[i].c == 0)
			ft_printf("{W}00");
		else if (memory[i].owner == &g_pls[0])
			ft_printf("{B}%.2hhx", memory[i].c);
		else if (memory[i].owner == &g_pls[1])
			ft_printf("{R}%.2hhx", memory[i].c);
		else if (memory[i].owner == &g_pls[2])
			ft_printf("{Y}%.2hhx", memory[i].c);
		else if (memory[i].owner == &g_pls[3])
			ft_printf("{G}%.2hhx", memory[i].c);
		if (i % 32 != 31)
			ft_printf(" ");
	}
	ft_printf("\n");
	free(g_memory);
	exit(0);
}

void	check_cycle(int total_live)
{
	t_process	*tmp;
	t_process	*t2;

	if (total_live >= NBR_LIVE || g_checks >= MAX_CHECKS)
	{
		if (g_cycle_die < CYCLE_DELTA)
			g_cycle_die = 0;
		else
			g_cycle_die -= CYCLE_DELTA;
		if (g_cycle_die == 0)
			g_gameover = 1;
		g_checks = 0;
	}
	else
		g_checks++;
	tmp = g_processes;
	while (tmp)
	{
		t2 = tmp->nx;
		if (!tmp->live)
			remove_process(tmp);
		else
			tmp->live = 0;
		tmp = t2;
	}
}

void	check(void)
{
	int	i;
	int	total_live;

	if (!(g_cur_cycle % g_cycle_die))
	{
		i = -1;
		total_live = 0;
		while (++i < g_pl && g_pls[i].name)
		{
			total_live += g_pls[i].lives;
			g_pls[i].lives = 0;
		}
		check_cycle(total_live);
		if (g_nproc <= 0)
			g_gameover = 1;
		g_cur_cycle = 0;
	}
}

void	update_processes(void)
{
	t_process	*tmp;

	if (g_total_cycle == g_dump_core)
		hexdumper(g_memory);
	tmp = g_processes;
	while (tmp)
	{
		tmp->pc = safe_mod(tmp->pc);
		if (tmp->wait <= 0 && !check_for_command(tmp))
		{
			if (tmp->wait <= 0)
				tmp->pc++;
		}
		else if (tmp->wait == 1 && tmp->wait-- >= 0)
			tmp->post_wait->func(tmp);
		else
			tmp->wait--;
		tmp->pc = safe_mod(tmp->pc);
		g_memory[tmp->pc].process = true;
		g_memory[tmp->pc].change = 1;
		tmp = tmp->nx;
	}
	g_total_cycle++;
}
