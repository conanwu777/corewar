/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   support.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/08 16:52:12 by cwu               #+#    #+#             */
/*   Updated: 2018/08/08 16:52:18 by cwu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "visual.h"

void	set_registry(t_process *pr, int reg, int val)
{
	int i;

	i = 0;
	if (reg - 1 < 0 || reg - 1 > 15)
		return ;
	pr->r[reg - 1][0] = val >> 24;
	pr->r[reg - 1][1] = val >> 16;
	pr->r[reg - 1][2] = val >> 8;
	pr->r[reg - 1][3] = val;
}

bool	get_registry(t_process *pr, int reg, int *val)
{
	*val = 0;
	if (reg - 1 < 0 || reg - 1 > 15)
		return (false);
	*val += pr->r[reg - 1][0] << 24;
	*val += pr->r[reg - 1][1] << 16;
	*val += pr->r[reg - 1][2] << 8;
	*val += pr->r[reg - 1][3];
	return (true);
}

void	start_process(int st_pos, t_player *p)
{
	t_process	*tmp;
	int			i;

	tmp = (t_process*)malloc(sizeof(t_process));
	tmp->pc = st_pos;
	tmp->owner = p;
	tmp->carry = false;
	tmp->wait = 0;
	tmp->live = 0;
	set_registry(tmp, 1, 0xffffffff - tmp->owner->id + 1);
	i = 1;
	while (++i < REG_NUMBER)
		set_registry(tmp, i, 0);
	tmp->nx = g_processes;
	g_processes = tmp;
	g_nproc++;
}

void	new_process(int pc, t_process *process)
{
	t_process	*tmp;
	int			i;
	int			reg;

	if (pc >= MEM_SIZE)
		pc -= MEM_SIZE;
	if ((tmp = (t_process*)malloc(sizeof(t_process))) == NULL)
		return ;
	tmp->pc = safe_mod(pc);
	tmp->owner = process->owner;
	tmp->carry = process->carry;
	tmp->live = process->live;
	tmp->wait = 0;
	tmp->post_wait = NULL;
	i = 0;
	while (++i < REG_NUMBER)
	{
		get_registry(process, i, &reg);
		set_registry(tmp, i, reg);
	}
	tmp->nx = g_processes;
	g_processes = tmp;
	g_nproc++;
}

void	remove_process(t_process *rm)
{
	t_process *cur;
	t_process *pv;

	pv = NULL;
	cur = g_processes;
	while (cur && cur != rm)
	{
		pv = cur;
		cur = cur->nx;
	}
	if (cur == rm)
	{
		if (pv)
			pv->nx = cur->nx;
		else
			g_processes = rm->nx;
		free(rm);
	}
	g_nproc--;
}
