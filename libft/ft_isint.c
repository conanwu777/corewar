/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isint.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/24 01:31:59 by cwu               #+#    #+#             */
/*   Updated: 2018/05/24 01:32:00 by cwu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isint(char *str)
{
	unsigned int	i;
	char			c;

	if (!str || (str[0] == '-' && ft_strlen(str) == 1))
		return (0);
	i = 0;
	if (str[i] == '-')
		i++;
	i--;
	while (++i < ft_strlen(str))
		if (!ft_isdigit(str[i]))
			return (0);
	if (ft_strlen(str) > 11 || (str[0] != '-' && ft_strlen(str) > 10))
		return (0);
	if (ft_strlen(str) < 10 || (str[0] == '-' && ft_strlen(str) < 11))
		return (1);
	c = str[ft_strlen(str) - 1];
	str[ft_strlen(str) - 1] = '\0';
	if (ft_atoi(str) > 214748364 || ft_atoi(str) < -214748364
		|| (ft_atoi(str) == 214748364 && c > '7')
		|| (ft_atoi(str) == -214748364 && c > '8'))
		return (0);
	return (1);
}
