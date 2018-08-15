/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual_support.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/09 03:42:16 by cwu               #+#    #+#             */
/*   Updated: 2018/08/09 03:42:21 by cwu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "visual.h"

unsigned int g_color[8];

unsigned int	t_color(float t, unsigned int c_st, unsigned int c_ed)
{
	unsigned int r;
	unsigned int g;
	unsigned int b;

	r = (unsigned int)((c_st >> 16) * (1 - t) + (c_ed >> 16) * t);
	g = (unsigned int)((c_st >> 8 & 255) * (1 - t) + (c_ed >> 8 & 255) * t);
	b = (unsigned int)((c_st & 255) * (1 - t) + (c_ed & 255) * t);
	return ((unsigned int)((r << 16) + (g << 8) + b));
}

void			put_cell(int x, int y, unsigned int c)
{
	int i;
	int j;

	i = -1;
	while (++i < 17)
	{
		j = -1;
		while (++j < 17)
			((unsigned int*)g_str)
		[((y + 8) * 20 + j + 2) * W + x * 20 + i + 2] = c;
	}
}

static int		check_player_lives(int i)
{
	int p;
	int j;

	p = -1;
	while (++p < g_pl)
	{
		if (g_memory[i].c == 1 && get_bytes(i + 1, 4) + g_pls[p].id == 0)
		{
			if (g_memory[i].change)
			{
				g_memory[i].color = g_pls[p].c1;
				j = 0;
				while (++j <= 4)
				{
					g_memory[i + j].color = g_pls[p].c2;
					g_memory[i + j].change = 1;
				}
			}
			return (1);
		}
	}
	return (0);
}

int				color_cell(int i)
{
	if (g_memory[i].process)
	{
		g_memory[i].color = 0xffffff;
		return (i + 1);
	}
	if (check_player_lives(i))
		return (i + 5);
	if (0 < g_memory[i].c && g_memory[i].c <= 16)
	{
		if (g_memory[i].change)
			g_memory[i].color = g_memory[i].owner->c1;
		return (i + 1);
	}
	if (g_memory[i].change)
		g_memory[i].color =
	t_color((float)g_memory[i].c / 256, 0x131e2d, 0x707b89);
	return (i + 1);
}

int				k_control(int key)
{
	if (key == 53)
	{
		mlx_destroy_image(g_mlx, g_img);
		exit(1);
	}
	if (key == 49)
		g_pause = !g_pause;
	if (key == 36)
	{
		g_step = 1;
		g_pause = 0;
	}
	if (key == 34)
		g_letters = !g_letters;
	return (1);
}
