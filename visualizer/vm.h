/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgleason <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/11 21:29:34 by cgleason          #+#    #+#             */
/*   Updated: 2018/07/11 21:29:51 by cgleason         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include "../libft/libft.h"
# include "../libft/ft_printf.h"
# include "just_one_struct.h"

# define IND_SIZE				2
# define REG_SIZE				4
# define DIR_SIZE				REG_SIZE

# define REG_CODE				1
# define DIR_CODE				2
# define IND_CODE				3

# define MAX_ARGS_NUMBER		4
# define MAX_PLAYERS			4
# define MEM_SIZE				(4*1024)
# define IDX_MOD				(MEM_SIZE / 8)
# define CHAMP_MAX_SIZE			(MEM_SIZE / 6)

# define COMMENT_CHAR			'#'
# define LABEL_CHAR				':'
# define DIRECT_CHAR			'%'
# define SEPARATOR_CHAR			','

# define LABEL_CHARS			"abcdefghijklmnopqrstuvwxyz_0123456789"

# define NAME_CMD_STRING		".name"
# define COMMENT_CMD_STRING		".comment"

# define REG_NUMBER				16

# define CYCLE_TO_DIE			1536
# define CYCLE_DELTA			50
# define NBR_LIVE				21
# define MAX_CHECKS				10

# define T_REG					1
# define T_DIR					2
# define T_IND					4
# define T_LAB					8

# define PROG_NAME_LENGTH		(128)
# define COMMENT_LENGTH			(2048)
# define COREWAR_EXEC_MAGIC		0xf383ea00

typedef struct			s_process
{
	int							pc;
	t_player					*owner;
	int							wait;
	t_byte						r[16][4];
	bool						carry;
	bool						live;
	t_op						*post_wait;
	struct s_process			*nx;
}						t_process;

typedef struct			s_opvars
{
	int		a1;
	int		a2;
	int		r;
	int		cb;
	int		sub;
	bool	b;
}						t_opvars;

int						safe_mod(int i);
void					live_01(t_process *process);
void					ld_02(t_process *process);
void					st_03(t_process *process);
void					add_04(t_process *process);
void					sub_05(t_process *process);
void					and_06(t_process *process);
void					or_07(t_process *process);
void					xor_08(t_process *process);
void					zjmp_09(t_process *process);
void					ldi_10(t_process *process);
void					sti_11(t_process *process);
void					fork_12(t_process *process);
void					lld_13(t_process *process);
void					lldi_14(t_process *process);
void					lfork_15(t_process *process);
void					aff_16(t_process *process);

void					new_process(int pc, t_process *process);
void					remove_process(t_process *process);
void					start_process(int st_pos, t_player *p);
bool					get_registry(t_process *pr, int reg, int *val);
void					set_registry(t_process *pr, int reg, int val);
void					check(void);
void					update_processes();
void					*memalloc(size_t size);
int						get_bytes(int pc, int n);
int						back_check(int pos, bool idx);
int						four_back_check(int pos, bool idx);

unsigned int			champ_size(int fd);
char					*champ_name(int fd);
int						execute_option(int ac, char **av, int i, int *pl_num);
int						print_usage(void);
void					init_variables(int ac, char **av);
void					pls_init(int ac, char **av);
void					set_start_color(void);

void					clear_and_free(int i);

t_mem					*g_memory;
t_process				*g_processes;
int						g_nproc;
int						g_pl;
t_player				*g_pls;
int						g_cur_cycle;
int						g_cycle_die;
int						g_checks;
bool					g_pause;
bool					g_step;
bool					g_gameover;
int						g_total_cycle;
int						g_dump_core;
int						g_visual;
t_player				*g_winner;

#endif
