/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freers.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgleason <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 23:07:46 by cgleason          #+#    #+#             */
/*   Updated: 2018/08/13 23:08:07 by cgleason         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "visual.h"

void	pony_maker(char *path, char *pony_path, int ind)
{
	char	*true_path;
	void	*img;
	int		db;

	true_path = ft_strjoin(path, pony_path);
	img = mlx_xpm_file_to_image(g_mlx, true_path, &db, &db);
	g_pony[ind] = mlx_get_data_addr(img, &db, &db, &db);
	free(true_path);
}

void	clear_and_free(int i)
{
	int	j;

	if (i == 1)
		ft_printf("{R}Invalid .cor file\n");
	else if (i == 2)
		print_usage();
	j = -1;
	while (g_pls[++j].name != NULL)
	{
		free(g_pls[j].name);
		free(g_pls[j].comment);
	}
	free(g_pls);
	free(g_memory);
	if (g_visual && g_img && g_mlx)
		mlx_destroy_image(g_mlx, g_img);
	if (i != 0)
		exit(i);
}
