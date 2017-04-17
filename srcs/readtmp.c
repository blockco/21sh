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

char *checkarrowkeys(char *str1, t_shell *shell, char *ret)
{
	shell->lineinfo->size = ft_strlen(ret);
	if (str1[2] == 'C') 		//right
	{
		if (shell->lineinfo->linespot > 0)
		{
			shell->lineinfo->linespot--;
			RIGHT;
		}
	}
	else if (str1[2] == 'D')	//left
	{
		if (shell->lineinfo->size > shell->lineinfo->linespot)
		{
			LEFT;
			shell->lineinfo->linespot++;
		}
	}
	else if (str1[2] == 'A') 	//up
	{
		if (shell->lineinfo->spot_hist < (int)shell->history->size - 1)
		{
			LINE;
			CLEAR_LN;
			print_interp();
			shell->lineinfo->spot_hist++;
			ft_putstr(*(char **)vectspot(shell->lineinfo->spot_hist, shell->history));
			return(ft_strdup(*(char **)vectspot(shell->lineinfo->spot_hist, shell->history)));
		}
	}
	else if (str1[2] == 'B')	//down
	{
		LINE;
		CLEAR_LN;
		print_interp();
		if (shell->lineinfo->linespot > -1)
		{
			shell->lineinfo->spot_hist--;
			if (shell->lineinfo->spot_hist > -1)
			{
				ft_putstr(*(char **)vectspot(shell->lineinfo->spot_hist, shell->history));
				return(ft_strdup(*(char **)vectspot(shell->lineinfo->spot_hist, shell->history)));
			}
		}
	}
	else if (str1[0] == 127)
	{
		if (shell->lineinfo->linespot < (int)ft_strlen(ret))
		{
			shell->lineinfo->size--;
			LEFT;
			DEL_CHAR;
			del_fun(ret, shell->lineinfo->linespot);
		}
	}
	return(ft_strjoin(ret, ""));
}

char	*read_tmp(t_shell *shell)
{
	char		*str1;
	char		*ret;
	char		*tmp;
	t_vector	*vect;
	vect = vect_new(10, sizeof(char*));
	str1 = ft_strnew(BUFF_SIZE);
	ret = ft_strdup("");
	termresetline(shell);
	while (1)
	{
		vect_insert(vect, vect->size, &str1);
		str1 = ft_strnew(BUFF_SIZE);
		vect_insert(vect, vect->size, &ret);
		read(0, str1, BUFF_SIZE);
		if (check_char(str1, shell))
		{
			ret = addtobuff(shell, ret, str1);
			INSERT_MODE_ON;
			ft_putstr(str1);
			INSERT_MODE_OFF;
			shell->lineinfo->size++;
		}
		else
			ret = checkarrowkeys(str1, shell, ret);
		if (str1[0] == 13 && !shell->lineinfo->dq)
			break;
		if (shell->lineinfo->dq && str1[0] == 13)
		{
			shell->endl++;
			ft_putchar('\n');
		}
	}
	if (ft_strcmp("", ret) && shell->lineinfo->spot_hist == -1 && ft_strcmp(vectspot(0, shell->history), ret) != 0)
	{
		tmp = ft_strdup(ret);
		vect_insert(shell->history, 0, &tmp);
	}
	while (shell->endl)
	{
		shell->endl--;
		insert_char("\n");
	}
	col_vect(vect);
	//history not freed
	return (ret);
}
