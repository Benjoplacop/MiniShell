/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbilly <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 15:32:45 by mbilly            #+#    #+#             */
/*   Updated: 2023/02/16 10:55:01 by mbilly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static int	nblen(int n)
{
	int	res;

	res = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		res++;
		n *= -1;
	}
	while (n > 0)
	{
		res++;
		n = n / 10;
	}
	return (res);
}

static void	set_str(char *str, int size, int n)
{
	if (n == 0)
	{
		str[0] = 48;
		str[1] = 0;
	}
	if (n < 0)
	{
		str[0] = '-';
		n *= -1;
	}
	while (n > 0)
	{
		str[size] = 48 + (n % 10);
		n = n / 10;
		size--;
	}
}

static char	*itoa_int_min(char *res, int n)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = (char *)malloc(sizeof(char) * nblen(n + 1) + 1);
	if (!tmp)
		return (NULL);
	while (res[i])
	{
		tmp[i] = res[i];
		i++;
	}
	tmp[i] = '\0';
	return (tmp);
}

char	*ft_itoa(int n)
{
	char	*tmp;

	if (n == -2147483648)
		return (itoa_int_min("-2147483648", n));
	else
	{
		tmp = (char *)malloc(sizeof(char) * nblen(n) + 1);
		if (!tmp)
			return (NULL);
		tmp[nblen(n)] = '\0';
		set_str(tmp, nblen(n) - 1, n);
		if (!tmp)
			return (NULL);
	}
	return (tmp);
}
