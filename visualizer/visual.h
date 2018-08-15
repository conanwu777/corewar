/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/08 19:41:37 by cwu               #+#    #+#             */
/*   Updated: 2018/08/08 19:41:42 by cwu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VISUAL_H
# define VISUAL_H

# include <pthread.h>
# include "minilibx_macos/mlx.h"
# define PIX	mlx_pixel_put
# define STR	mlx_string_put
# define LEN	128
# define W		LEN*20
# define H		1200

void			*g_mlx;
void			*g_win;
void			*g_img;
char			*g_str;
bool			g_letters;
char			*g_pony[4];

void			minilibx_init(char **av);
void			update_info(void);
int				k_control(int key);
int				refresh(void);
int				color_cell(int i);
void			put_cell(int x, int y, unsigned int c);
unsigned int	t_color(float t, unsigned int c_st, unsigned int c_ed);
void			bar_chart(void);
void			pony(void);
void			pony_maker(char *path, char *pony_path, int ind);

#endif
