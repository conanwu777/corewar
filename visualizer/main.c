/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgleason <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/12 15:41:41 by cgleason          #+#    #+#             */
/*   Updated: 2018/07/12 15:42:56 by cgleason         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "visual.h"

unsigned int	champ_size(int fd)
{
	unsigned int	test;
	int				tmp;

	lseek(fd, PROG_NAME_LENGTH + 8, SEEK_SET);
	test = 0;
	tmp = 0;
	read(fd, (void*)&tmp, 1);
	test += tmp << 24;
	read(fd, (void*)&tmp, 1);
	test += tmp << 16;
	read(fd, (void*)&tmp, 1);
	test += tmp << 8;
	read(fd, (void*)&tmp, 1);
	test += tmp;
	return (test);
}

int				execute_option(int ac, char **av, int i, int *pl_num)
{
	if (i > ac - 2)
		return (0);
	if (!ft_strcmp(av[i] + 1, "dump"))
	{
		g_dump_core = ft_atoi(av[i + 1]);
		g_visual = 0;
		return (i + 2);
	}
	else if (!ft_strcmp(av[i] + 1, "n"))
	{
		*pl_num = ft_atoi(av[i + 1]);
		return (i + 2);
	}
	else if (!ft_strcmp(av[i] + 1, "q"))
	{
		g_visual = 0;
		return (i + 1);
	}
	return (0);
}

int				print_usage(void)
{
	ft_printf("{O}usage: ./corewar [-dump nbr_cycles] [-q]\n");
	ft_printf("{O}[[-n number] champion1.cor] [[-n number] champion2.cor]\n");
	ft_printf("{O}[[-n number] champion3.cor] [[-n number] champion4.cor]\n");
	return (0);
}

static void		visual_start(char **av)
{
	int i;

	minilibx_init(av);
	i = 0;
	while (i < MEM_SIZE)
		i = color_cell(i);
	i = -1;
	while (++i < MEM_SIZE)
		if (g_memory[i].change)
			put_cell(i % LEN, i / LEN, g_memory[i].color);
	mlx_hook(g_win, 2, 0, &k_control, (void*)0);
	mlx_loop_hook(g_mlx, &refresh, (void*)0);
	mlx_loop(g_mlx);
}

int				main(int ac, char **av)
{
	if (ac > 15 || ac < 2)
		return (print_usage());
	g_memory = (t_mem *)malloc(sizeof(t_mem) * MEM_SIZE);
	if (g_memory == NULL)
		return (ft_putendl_fd("Insufficient memory for virtual machine", 2));
	init_variables(ac, av);
	if (g_visual)
		visual_start(av);
	else
		while (!g_gameover)
		{
			update_processes();
			g_cur_cycle++;
			check();
		}
	if (g_winner)
	{
		ft_printf("{G}\nGameover: Player %d, %s, has won!\n",
			g_winner->id, g_winner->name);
		ft_printf("{W}%s\n", g_winner->comment);
	}
	else
		ft_printf("{R}\nNOBODY CALLED LIVE. NOT EVEN ONCE.\n");
	clear_and_free(0);
	return (0);
}
