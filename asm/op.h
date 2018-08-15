/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgleason <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/08 16:35:55 by cgleason          #+#    #+#             */
/*   Updated: 2018/08/08 16:35:58 by cgleason         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OP_H
# define OP_H

# include <unistd.h>
# include "../libft/libft.h"
# include "../libft/ft_printf.h"
# include <stdbool.h>
# include <fcntl.h>

# define IND_SIZE			2
# define REG_SIZE			4
# define DIR_SIZE			REG_SIZE

# define REG_CODE			1
# define DIR_CODE			2
# define IND_CODE			3

# define MAX_ARGS_NUMBER	4
# define MAX_PLAYERS		4
# define MEM_SIZE			(4*1024)
# define IDX_MOD			(MEM_SIZE / 8)
# define CHAMP_MAX_SIZE		(MEM_SIZE / 6)

# define COMMENT_CHAR		'#'
# define LABEL_CHAR			':'
# define DIRECT_CHAR		'%'
# define SEPARATOR_CHAR		','

# define LABEL_CHARS		"abcdefghijklmnopqrstuvwxyz_0123456789"

# define NAME_CMD_STRING	".name"
# define COMMENT_CMD_STRING	".comment"

# define REG_NUMBER			16

# define CYCLE_TO_DIE		1536
# define CYCLE_DELTA		50
# define NBR_LIVE			21
# define MAX_CHECKS			10

# define T_REG				1
# define T_DIR				2
# define T_IND				4
# define T_LAB				8

# define PROG_NAME_LENGTH	(128)
# define COMMENT_LENGTH		(2048)
# define HEADER_LENGTH		(PROG_NAME_LENGTH + 8 + COMMENT_LENGTH + 8)
# define CHAMP_LENGTH		(HEADER_LENGTH + CHAMP_MAX_SIZE)
# define COREWAR_EXEC_MAGIC	0xea83f3

typedef enum	e_err_msg
{
	eusage,
	einvalid,
	enomem,
	einvlbl,
	enocomment,
	elgcomment,
	enoname,
	elgname,
	eundlbl,
	elongpar,
	einvpar,
	eshrtpar,
	einvcom,
	einvnum,
}				t_err_msg;

typedef struct	s_header
{
	unsigned int		magic;
	char				prog_name[PROG_NAME_LENGTH + 1];
	unsigned int		prog_size;
	char				comment[COMMENT_LENGTH + 1];
}				t_header;

typedef struct	s_output
{
	unsigned short	addr;
	unsigned short	laddr;
	unsigned char	bytes;
}				t_output;

typedef struct	s_lbl
{
	bool			found;
	char			*name;
	unsigned short	loc;
	t_output		*outputs;
	int				nout;
	struct s_lbl	*nx;
}				t_lbl;

typedef struct	s_nums
{
	int				i;
	int				j;
	int				k;
	int				tmp;
	unsigned char	c;
}				t_nums;

typedef struct	s_op
{
	char			*opcode;
	unsigned char	byte;
	bool			coding_byte;
	size_t			input_len;
	unsigned char	input[3];
	bool			dir_two;
}				t_op;

int				g_line;
short			g_count;
short			g_countl;
t_lbl			*g_labels;
int				g_rd;
int				g_out;
unsigned char	*g_name;
unsigned char	*g_comment;
t_header		g_header;
unsigned char	g_buf[CHAMP_LENGTH * 10];

int				convert(char *name, char *input);
void			put_bytes(unsigned char *t, int bts);

void			add_field(unsigned char *field, int size);
int				no_name_comment(bool c, char *line);
int				get_name_comment(int fd, bool c);
void			remove_comments(char **line);
void			check_label_name(char *name);

void			help_with_label(char *line, int i, t_lbl *tmp, t_lbl *lbl);
void			check_for_label(char **line);
void			new_label(char *name, int bts);
void			add_label(char *name, int bts);
void			incert_labels(void);

bool			is_number(char *str);
bool			check_type(char **tab, unsigned char *input, int len);
unsigned char	coding_byte(char **tab);
void			put_bytes(unsigned char *t, int bts);
void			str_trim(char **str);

void			free_and_clear(t_err_msg ind);

#endif
