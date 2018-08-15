/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 17:03:00 by cwu               #+#    #+#             */
/*   Updated: 2018/08/13 17:03:01 by cwu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "visual.h"

t_op			g_optab[17];

unsigned int	g_color[8] = {
	0x2c2099,
	0xc18e00,
	0x169baf,
	0xaa3a4e,
	0xc4cbff,
	0xffec5e,
	0xc4fff5,
	0xffcee0
};

void	minilibx_init(char **av)
{
	int		db;

	av[0][ft_strlen(av[0]) - 7] = '\0';
	g_letters = 1;
	g_mlx = mlx_init();
	g_win = mlx_new_window(g_mlx, W, H, "corewar");
	g_img = mlx_new_image(g_mlx, W, H);
	g_str = mlx_get_data_addr(g_img, &db, &db, &db);
	pony_maker(av[0], "ponies/rarity.XPM", 0);
	pony_maker(av[0], "ponies/fluttershy.XPM", 1);
	pony_maker(av[0], "ponies/rainbowdash.XPM", 2);
	pony_maker(av[0], "ponies/pinkypie.XPM", 3);
}

void	*cell_thread(void *p)
{
	int mod;
	int pos;

	mod = *((int*)p);
	pos = -1;
	while (++pos < MEM_SIZE)
		if (g_memory[pos].change && pos % 4 == mod)
			put_cell(pos % LEN, pos / LEN, g_memory[pos].color);
	return (NULL);
}

void	thread_grid(void)
{
	int			mod[4];
	int			i;
	pthread_t	thread[4];

	i = 0;
	while (i < 4)
	{
		mod[i] = i;
		pthread_create(&(thread[i]), NULL, cell_thread, (void*)(&mod[i]));
		i++;
	}
	i = 0;
	while (i < 4)
	{
		pthread_join(thread[i], NULL);
		i++;
	}
}

void	refresh_data(int i)
{
	if (g_step)
	{
		g_step = 0;
		g_pause = 1;
	}
	while (++i < MEM_SIZE)
		if (g_memory[i].process)
		{
			g_memory[i].process = 0;
			g_memory[i].change = 1;
		}
		else
			g_memory[i].change = 0;
	update_processes();
	i = 0;
	while (i < MEM_SIZE)
		i = color_cell(i);
	i = -1;
	thread_grid();
	g_cur_cycle++;
	if (!(g_cur_cycle % g_cycle_die))
	{
		check();
		g_cur_cycle = 0;
	}
}

int		refresh(void)
{
	int i;

	i = -1;
	if (!g_gameover && !g_pause)
		refresh_data(i);
	bar_chart();
	if (g_winner)
		pony();
	mlx_put_image_to_window(g_mlx, g_win, g_img, 0, 0);
	if (g_letters)
	{
		i = -1;
		while (++i < MEM_SIZE)
			if (0 < g_memory[i].c && g_memory[i].c <= 16)
				STR(g_mlx, g_win, i % LEN * 20 + 5, (8 + i / LEN) * 20 - 2,
					g_memory[i].owner->c2, g_optab[g_memory[i].c - 1].opcode);
	}
	if (g_gameover)
	{
		g_cycle_die = 0;
		g_cur_cycle = 0;
	}
	update_info();
	return (0);
}
