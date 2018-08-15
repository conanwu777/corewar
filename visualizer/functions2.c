/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/08 17:06:15 by cwu               #+#    #+#             */
/*   Updated: 2018/08/08 17:06:17 by cwu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	ld_02(t_process *process)
{
	t_byte	cb;
	int		pos;
	int		r;

	cb = get_bytes(process->pc + 1, 1);
	if (cb >> 6 == DIR_CODE)
	{
		r = get_bytes((process->pc + 6) % MEM_SIZE, 1);
		pos = get_bytes((process->pc + 2) % MEM_SIZE, 4);
		set_registry(process, r, pos);
		process->pc += 7;
	}
	else
	{
		r = get_bytes((process->pc + 4) % MEM_SIZE, 1);
		pos = get_bytes((process->pc + 2) % MEM_SIZE, 2);
		pos = back_check(pos, 1);
		set_registry(process, r,
			get_bytes((process->pc + pos + MEM_SIZE) % MEM_SIZE, 4));
		process->pc += 5;
	}
	if (get_registry(process, r, &pos) != 0 && pos == 0)
		process->carry = true;
	else
		process->carry = false;
}

void	lld_13(t_process *process)
{
	t_byte	cb;
	int		r;
	int		reg;

	cb = get_bytes(process->pc + 1, 1);
	if (cb >> 6 == DIR_CODE)
	{
		r = get_bytes(process->pc + 6, 1);
		set_registry(process, r, get_bytes(process->pc + 2, 4));
		process->pc += 7;
	}
	else
	{
		r = get_bytes(process->pc + 4, 1);
		set_registry(process, r,
			get_bytes(process->pc +
				back_check(get_bytes(process->pc + 2, 2), 0), 4));
		process->pc += 5;
	}
	if (get_registry(process, r, &reg) != 0 && reg == 0)
		process->carry = true;
	else
		process->carry = false;
}

void	add_04(t_process *process)
{
	int r3;
	int i;
	int t1;
	int t2;

	r3 = get_bytes(process->pc + 4, 1);
	process->carry = true;
	i = 0;
	get_registry(process, get_bytes(process->pc + 2, 1), &t1);
	get_registry(process, get_bytes(process->pc + 3, 1), &t2);
	set_registry(process, r3, t1 + t2);
	if (t1 + t2 != 0)
		process->carry = false;
	process->pc += 5;
}

void	sub_05(t_process *process)
{
	int r3;
	int i;
	int t1;
	int t2;

	r3 = get_bytes(process->pc + 4, 1);
	process->carry = true;
	i = 0;
	get_registry(process, get_bytes(process->pc + 2, 1), &t1);
	get_registry(process, get_bytes(process->pc + 3, 1), &t2);
	set_registry(process, r3, t1 - t2);
	if (t1 - t2 != 0)
		process->carry = false;
	process->pc += 5;
}

void	aff_16(t_process *process)
{
	int	to_put;

	if (get_registry(process, get_bytes(process->pc + 2, 1), &to_put) == 1)
		ft_putchar((char)(to_put % 256));
	process->pc += 3;
}
