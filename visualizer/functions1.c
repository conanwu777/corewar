/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/08 17:04:06 by cwu               #+#    #+#             */
/*   Updated: 2018/08/08 17:04:18 by cwu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		get_bytes(int pc, int n)
{
	int val;
	int i;

	val = 0;
	i = -1;
	while (++i < n)
	{
		val = val << 8;
		val += g_memory[safe_mod(pc + i)].c;
	}
	return (val);
}

int		back_check(int pos, bool idx)
{
	if (idx)
	{
		if (pos < 0x7fff)
			pos = pos % IDX_MOD;
		else
			pos = -((0xffff + 1 - pos) % IDX_MOD);
		return (pos);
	}
	if (!(pos < 0x7fff))
		pos = -(0xffff + 1 - pos);
	return (pos);
}

int		four_back_check(int pos, bool idx)
{
	if (idx)
	{
		if (pos < 0x7fffffff)
			pos = pos % IDX_MOD;
		else
			pos = -((0xffffffff + (1 - pos)) % IDX_MOD);
		return (pos);
	}
	if (!(pos < 0x7fffffff))
		pos = -(0xffffffff + (1 - pos));
	return (pos);
}

void	live_01(t_process *process)
{
	int i;

	i = -1;
	while (++i < g_pl)
		if (g_pls[i].id + get_bytes(process->pc + 1, 4) == 0)
		{
			g_winner = &g_pls[i];
			g_pls[i].lives++;
		}
	process->live = 1;
	process->pc += 5;
}

void	zjmp_09(t_process *process)
{
	int jmp;

	if (process->carry == 1)
	{
		jmp = get_bytes(process->pc + 1, 2);
		process->pc += back_check(jmp, 1);
	}
	else
		process->pc += 3;
}
