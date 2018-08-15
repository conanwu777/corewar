/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   funstions3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/08 17:10:41 by cwu               #+#    #+#             */
/*   Updated: 2018/08/08 17:10:45 by cwu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "visual.h"

unsigned int	g_color[8];

static void	finish_store(t_process *proc, int pos, bool b)
{
	int i;
	int t;
	int r;

	r = get_bytes(proc->pc + 2, 1);
	if (r < 1 || r > 16)
		return ;
	i = 0;
	while (!b && i < 4)
	{
		t = safe_mod(proc->pc + pos + i);
		g_memory[t].c = proc->r[r - 1][i];
		if (g_visual)
		{
			if (g_memory[t].owner)
				g_memory[t].owner->total_occupied--;
			g_memory[t].owner = proc->owner;
			g_memory[t].owner->total_occupied++;
			g_memory[t].change = 1;
		}
		i++;
	}
}

void		st_03(t_process *proc)
{
	t_byte	cb;
	int		pos;

	cb = get_bytes(proc->pc + 1, 1);
	if ((cb >> 4) % 4 == REG_CODE)
	{
		if (get_registry(proc, get_bytes(proc->pc + 2, 1), &pos))
			set_registry(proc, get_bytes(proc->pc + 3, 1), pos);
		proc->pc += 4;
	}
	else
	{
		pos = back_check(get_bytes(proc->pc + 3, 2), 1);
		finish_store(proc, pos, 0);
		proc->pc += 5;
	}
}

void		sti_11(t_process *proc)
{
	t_byte	cb;
	int		pos;
	int		a[2];
	int		flag;
	bool	b;

	b = false;
	flag = 0;
	cb = get_bytes(proc->pc + 1, 1);
	if ((cb >> 4) % 4 == REG_CODE && flag++ >= 0)
	{
		if (!get_registry(proc, get_bytes(proc->pc + 3, 1), &(a[0])))
			b = true;
	}
	else
		a[0] = (cb >> 4) % 4 == DIR_CODE ? get_bytes(proc->pc + 3, 2) :
		get_bytes(proc->pc + back_check(get_bytes(proc->pc + 3, 2), 1), 4);
	if ((cb >> 2) % 4 == DIR_CODE)
		a[1] = get_bytes(proc->pc + 5 - flag, 2);
	else if (flag++ >= 0)
		if (!get_registry(proc, get_bytes(proc->pc + 6 - flag, 1), &(a[1])))
			b = true;
	pos = (back_check(a[0], 0) + back_check(a[1], 0)) % IDX_MOD;
	finish_store(proc, pos, b);
	proc->pc += 7 - flag;
}

void		fork_12(t_process *process)
{
	int shift;

	shift = get_bytes(process->pc + 1, 2);
	shift = back_check(shift, 1);
	new_process(process->pc + shift, process);
	process->pc += 3;
}

void		lfork_15(t_process *process)
{
	int shift;

	shift = get_bytes(process->pc + 1, 2);
	shift = back_check(shift, 0);
	new_process(process->pc + shift, process);
	process->pc += 3;
}
