/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/08 19:10:45 by cwu               #+#    #+#             */
/*   Updated: 2018/08/08 19:10:49 by cwu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void	start_loading(t_process *process, t_opvars *vp, int *flag)
{
	*vp = (t_opvars){0, 0, 0, get_bytes(process->pc + 1, 1), 0, false};
	if (vp->cb >> 6 == DIR_CODE)
		vp->a1 = get_bytes(process->pc + 2, 2);
	else if (vp->cb >> 6 == REG_CODE)
	{
		if (!get_registry(process, get_bytes(process->pc + 2, 1), &vp->a1))
			vp->b = true;
		(*flag)++;
	}
	else
		vp->a1 = get_bytes(process->pc +
			back_check(get_bytes(process->pc + 2, 2), 0) % IDX_MOD, 4);
	if ((vp->cb >> 4) % 4 == DIR_CODE)
		vp->a2 = get_bytes(process->pc + 4 - *flag, 2);
	else
	{
		if (!get_registry(process,
			get_bytes(process->pc + 4 - *flag, 1), &vp->a2))
			vp->b = true;
		(*flag)++;
	}
}

void		ldi_10(t_process *process)
{
	t_opvars	v;
	int			flag;

	flag = 0;
	start_loading(process, &v, &flag);
	v.r = get_bytes(process->pc + 6 - flag, 1);
	if (v.b == false)
		set_registry(process, v.r,
			get_bytes(process->pc + (v.a1 + v.a2) % IDX_MOD, 4));
	process->pc += 7 - flag;
	if (get_registry(process, v.r, &flag) != 0 && flag == 0)
		process->carry = true;
	else
		process->carry = false;
}

void		lldi_14(t_process *process)
{
	t_opvars	v;
	int			reg;
	int			flag;

	flag = 0;
	start_loading(process, &v, &flag);
	v.r = get_bytes(process->pc + 6 - flag, 1);
	if (v.b == false)
		set_registry(process, v.r, get_bytes(process->pc + v.a1 + v.a2, 4));
	if (get_registry(process, v.r, &reg) != 0 && reg == 0)
		process->carry = true;
	else
		process->carry = false;
	process->pc += 7 - flag;
}

int			safe_mod(int i)
{
	i %= MEM_SIZE;
	while (i < 0)
	{
		i += MEM_SIZE;
	}
	return (i);
}
