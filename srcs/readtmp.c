/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readtmp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpassafa <rpassafa@student.42.us>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/16 00:26:40 by rpassafa          #+#    #+#             */
/*   Updated: 2017/02/16 00:26:49 by rpassafa         ###   ########.us       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	insert_char(char *c)
{
	INSERT_MODE_ON;
	tputs(c, 1, ft_putchar);
	INSRT_MODE_OFF;
}

void	insert_str(char *c)
{
	int i;

	i = 0;
	INSERT_MODE_ON;
	while (c[i])
	{
		insert_char(&c[i]);
		i++;
	}
	INSRT_MODE_OFF;
}

char	*read_tmp(void)
{
	char		*str1;
	int			bytes_read;
	char		*ret;
	t_vector	*vect;

	vect = vect_new(10, sizeof(char*));
	str1 = ft_strnew(BUFF_SIZE);
	ret = ft_strnew(1);
	bytes_read = 0;
	while (ft_strchr(ret, '\n') == NULL)
	{
		vect_insert(vect, vect->size, &str1);
		str1 = ft_strnew(BUFF_SIZE);
		if (bytes_read > 0)
		{
			vect_insert(vect, vect->size, &ret);
		}
		bytes_read += read(0, str1, BUFF_SIZE);
		insert_char(str1);
		if (bytes_read > 1)
			ret = ft_strjoin(ret, (const char*)str1);
		else
			ret = ft_strdup(str1);
		if (str1[0] == 13)
			break;
	}
	insert_char("\n");
	CLEAR_LN;
	col_vect(vect);
	ret[bytes_read - 1] = '\0';
	return (ret);
}
