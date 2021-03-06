/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpassafa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/01 14:40:23 by rpassafa          #+#    #+#             */
/*   Updated: 2016/10/01 14:40:25 by rpassafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr(int n)
{
	long s;

	s = n;
	if (s < 0)
	{
		ft_putchar('-');
		s = -1 * s;
	}
	if (s > 9)
		ft_putnbr(s / 10);
	ft_putchar(s % 10 + '0');
}
