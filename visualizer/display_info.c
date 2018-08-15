/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_info.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 17:03:39 by cwu               #+#    #+#             */
/*   Updated: 2018/08/13 17:03:40 by cwu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "visual.h"

t_op			g_optab[17];
unsigned int	g_color[8];

void		bar_chart(void)
{
	int i;
	int x;
	int y;
	int total;
	int partial;

	total = 0;
	i = -1;
	while (++i < g_pl)
		total += g_pls[i].total_occupied;
	i = -1;
	partial = 0;
	while (++i < g_pl)
	{
		y = H - 120;
		while (++y < H - 90)
		{
			x = W * partial / total - 1;
			while (++x < W * (partial + g_pls[i].total_occupied) / total)
				((unsigned int*)g_str)[y * W + x] = g_pls[i].c1;
		}
		partial += g_pls[i].total_occupied;
	}
}

void		pony(void)
{
	int i;
	int j;
	int pos;

	i = -1;
	while (++i < 159)
	{
		j = -1;
		while (++j < 159)
		{
			pos = (855 + j) * W + (70 + i);
			((unsigned int*)g_str)[pos] = ((unsigned int*)
				g_pony[g_winner->id - 1])[j * 159 + i];
		}
	}
}

static void	update_info2(int i)
{
	int				j;
	unsigned int	c;
	char			str[1024];

	while (++i < g_pl)
	{
		c = ((g_gameover && g_winner && g_winner->id != g_pls[i].id) ?
			0x848484 : t_color(0.5, g_color[i], g_color[i + 4]));
		sprintf(str, "Player %d: %.25s", i + 1, g_pls[i].name);
		STR(g_mlx, g_win, LEN * 5,
			(MEM_SIZE / LEN + 2 * (i + 1) + 9) * 20, c, str);
		sprintf(str, "%.45s", g_pls[i].comment);
		STR(g_mlx, g_win, LEN * 8,
			(MEM_SIZE / LEN + 2 * (i + 1) + 9) * 20, c, str);
		sprintf(str, "Lives cur period: %d", g_pls[i].lives);
		STR(g_mlx, g_win, LEN * 12,
			(MEM_SIZE / LEN + 2 * (i + 1) + 9) * 20, c, str);
		j = -1;
		while (++j < g_pls[i].lives && j < 70)
			str[j] = '*';
		str[j] = '\0';
		STR(g_mlx, g_win, LEN * 14,
			(MEM_SIZE / LEN + 2 * (i + 1) + 9) * 20, c, str);
	}
}

void		update_info(void)
{
	char			str[1024];

	if (g_gameover)
		STR(g_mlx, g_win, (LEN - 9) / 2 * 20,
			4 * 20, 0xffffff, "***GAMEOVER***");
	else if (g_pause)
		STR(g_mlx, g_win, (LEN - 10) / 2 * 20,
			4 * 20, 0xffffff, "***PAUSED***");
	else
		STR(g_mlx, g_win, (LEN - 10) / 2 * 20,
			4 * 20, 0xffffff, "***RUNNING***");
	sprintf(str, "Total cycle: %d", g_total_cycle);
	STR(g_mlx, g_win, 350, (MEM_SIZE / LEN + 11) * 20, 0xffffff, str);
	sprintf(str, "Cycle to die: %d", g_cycle_die);
	STR(g_mlx, g_win, 350, (MEM_SIZE / LEN + 13) * 20, 0xffffff, str);
	sprintf(str, "Countdown: %d", g_cycle_die - g_cur_cycle);
	STR(g_mlx, g_win, 350, (MEM_SIZE / LEN + 15) * 20, 0xffffff, str);
	sprintf(str, "Processes alive: %d", g_nproc);
	STR(g_mlx, g_win, 350, (MEM_SIZE / LEN + 17) * 20, 0xffffff, str);
	update_info2(-1);
}
