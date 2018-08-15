/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/08 18:38:38 by cwu               #+#    #+#             */
/*   Updated: 2018/08/08 18:38:40 by cwu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	start_op(t_process *process, t_opvars *v)
{
	if (v->cb >> 6 == DIR_CODE)
		v->a1 = get_bytes(process->pc + 2, 4);
	else if (v->cb >> 6 == REG_CODE)
	{
		if (!get_registry(process, get_bytes(process->pc + 2, 1), &(v->a1)))
			v->b = true;
		v->sub += 3;
	}
	else if ((v->sub += 2) > 0)
		v->a1 = get_bytes(process->pc +
		back_check(get_bytes(process->pc + 2, 2), 1), 4);
	if ((v->cb >> 4) % 4 == DIR_CODE)
		v->a2 = get_bytes(process->pc + 6 - v->sub, 4);
	else if ((v->cb >> 4) % 4 == REG_CODE)
	{
		if (!get_registry(process,
		get_bytes(process->pc + 6 - v->sub, 1), &(v->a2)))
			v->b = true;
		v->sub += 3;
	}
	else if ((v->sub += 2) > 0)
		v->a2 = get_bytes(process->pc +
		back_check(get_bytes(process->pc + 6 - v->sub, 2), 1), 4);
}

void	and_06(t_process *process)
{
	t_opvars	v;
	int			i;

	v.b = false;
	v.sub = 0;
	v.cb = get_bytes(process->pc + 1, 1);
	start_op(process, &v);
	v.r = get_bytes(process->pc + 10 - v.sub, 1);
	if (v.b)
	{
		process->pc += 11 - v.sub;
		return ;
	}
	process->carry = true;
	set_registry(process, v.r, v.a1 & v.a2);
	get_registry(process, v.r, &i);
	if (i != 0)
		process->carry = false;
	process->pc += 11 - v.sub;
}

void	or_07(t_process *process)
{
	t_opvars	v;
	int			i;

	v.b = false;
	v.sub = 0;
	v.cb = get_bytes(process->pc + 1, 1);
	start_op(process, &v);
	v.r = get_bytes(process->pc + 10 - v.sub, 1);
	if (v.b)
	{
		process->pc += 11 - v.sub;
		return ;
	}
	process->carry = true;
	set_registry(process, v.r, v.a1 | v.a2);
	get_registry(process, v.r, &i);
	if (i != 0)
		process->carry = false;
	process->pc += 11 - v.sub;
}

void	xor_08(t_process *process)
{
	t_opvars	v;
	int			i;

	v.b = false;
	v.sub = 0;
	v.cb = get_bytes(process->pc + 1, 1);
	start_op(process, &v);
	v.r = get_bytes(process->pc + 10 - v.sub, 1);
	if (v.b)
	{
		process->pc += 11 - v.sub;
		return ;
	}
	process->carry = true;
	set_registry(process, v.r, v.a1 ^ v.a2);
	get_registry(process, v.r, &i);
	if (i != 0)
		process->carry = false;
	process->pc += 11 - v.sub;
}
