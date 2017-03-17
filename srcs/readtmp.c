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

void	insert_str(char *cwd)
{
	int i;
	char *tmp;

	i = 0;
	INSERT_MODE_ON;
	while (cwd[i])
	{
		tmp = ft_strnew(2);
		tmp[0] = cwd[i++];
		insert_char(tmp);
		free (tmp);
		// ft_putchar(cwd[i++]);
	}
	INSERT_MODE_OFF;
}

void	insert_char(char *c)
{
	INSERT_MODE_ON;
	tputs(c, 1, ft_putchar);
	INSERT_MODE_OFF;
}

// void	insert_str(char *c)
// {
// 	int i;
//
// 	i = 0;
// 	INSERT_MODE_ON;
// 	while (c[i])
// 	{
// 		insert_char(&c[i]);
// 		i++;
// 	}
// 	INESRT_MODE_OFF;
// }

void return_print()
{
	char *str1;

	str1 = ft_strnew(2);
	str1[0] = 13;
	insert_str(str1);
	free(str1);
}

char	*read_tmp()
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
		insert_str(str1);
		if (bytes_read > 1)
			ret = ft_strjoin(ret, (const char*)str1);
		else
			ret = ft_strdup(str1);
		if (str1[0] == 13)
			break;
	}
	insert_char("\n");
	col_vect(vect);
	ret[bytes_read - 1] = '\0';
	LINE;
	return (ret);
}
