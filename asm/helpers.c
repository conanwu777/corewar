/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgleason <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/14 17:01:25 by cgleason          #+#    #+#             */
/*   Updated: 2018/08/14 17:01:31 by cgleason         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"

bool			is_number(char *str)
{
	int i;

	i = 0;
	while (str[i] == ' ')
		i++;
	if (str[i] == '-')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		i++;
	}
	if (str[i] == '\0')
		return (1);
	return (0);
}

bool			check_type(char **tab, unsigned char *input, int len)
{
	int				i;
	unsigned int	tmp;

	i = -1;
	while (tab[++i])
	{
		if (i >= len)
			free_and_clear(elongpar);
		tmp = input[i];
		if ((tab[i][0] == 'r' && (tmp & T_REG) == 0) ||
		(tab[i][0] == DIRECT_CHAR && (tmp & T_DIR) == 0) ||
		(tab[i][0] != 'r' && tab[i][0] != DIRECT_CHAR && (tmp & T_IND) == 0))
			free_and_clear(einvpar);
	}
	if (i < len)
		free_and_clear(eshrtpar);
	return (1);
}

unsigned char	coding_byte(char **tab)
{
	unsigned char	ret;
	int				i;

	i = 0;
	ret = 0;
	while (tab[i])
	{
		if (tab[i][0] == 'r')
			ret += REG_CODE;
		else if (tab[i][0] == '%')
			ret += DIR_CODE;
		else
			ret += IND_CODE;
		ret = ret << 2;
		i++;
	}
	while (i < 3)
	{
		ret = ret << 2;
		i++;
	}
	return (ret);
}

void			put_bytes(unsigned char *t, int bts)
{
	while (bts--)
		g_buf[g_count++] = t[bts];
}

void			str_trim(char **str)
{
	char	*trim;
	char	*new;
	int		i;
	int		num;

	trim = ft_strtrim(*str);
	new = ft_strnew(ft_strlen(*str));
	i = -1;
	num = 0;
	while (trim[i + 1] && trim[i + 2])
	{
		i++;
		if ((trim[i] == ' ' || trim[i] == '\t') &&
			(trim[i + 1] == ' ' || trim[i + 1] == '\t'))
			continue ;
		new[num] = trim[i];
		if (new[num] == '\t')
			new[num] = ' ';
		num++;
	}
	new[num] = trim[i + 1];
	free(trim);
	free(*str);
	*str = new;
}
