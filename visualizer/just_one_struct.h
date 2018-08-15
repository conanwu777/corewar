/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   just_one_struct.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgleason <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/08 20:46:10 by cgleason          #+#    #+#             */
/*   Updated: 2018/08/08 20:49:06 by cgleason         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JUST_ONE_STRUCT_H
# define JUST_ONE_STRUCT_H

# include <string.h>

typedef unsigned char		t_byte;

typedef struct				s_player
{
	int				fd;
	int				size;
	char			*name;
	char			*comment;
	unsigned int	id;
	int				lives;
	int				total_occupied;
	unsigned int	c1;
	unsigned int	c2;
}							t_player;

typedef struct				s_mem
{
	t_byte			c;
	bool			process;
	unsigned int	color;
	t_player		*owner;
	bool			change;
}							t_mem;

typedef struct s_process	t_process;

typedef struct				s_op
{
	char			*opcode;
	int				wait;
	void			(*func)(t_process *);
	bool			coding_byte;
	size_t			input_len;
	unsigned char	input[3];
	bool			dir_two;
}							t_op;

#endif
