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

void jumpleft(t_shell *shell, char *ret)
{
	int index;

	index = ft_strlen(ret) - shell->lineinfo->linespot;
	if (shell->lineinfo->linespot == 0)
	{
		LEFT;
		shell->lineinfo->linespot++;
		index--;
	}
	if (ret[index] == ' ')
	{
		while (index > 0 && ret[index] && ret[index] == ' ')
		{
			LEFT;
			shell->lineinfo->linespot++;
			index--;
		}
	}
	else
	{
		while (index > 0 && ret[index] && ret[index] != ' ')
		{
			LEFT;
			shell->lineinfo->linespot++;
			index--;
		}
	}
}

void jumpright(t_shell *shell, char *ret)
{
	int index;

	index = ft_strlen(ret) - shell->lineinfo->linespot;

	if (ret[index] == ' ')
	{
		while(ret[index] && ret[index] == ' ')
		{
			shell->lineinfo->linespot--;
			RIGHT;
			index++;
		}
	}
	else
	{
		while (ret[index] && ret[index] != ' ')
		{
			shell->lineinfo->linespot--;
			RIGHT;
			index++;
		}
	}
}

char *checkarrowkeys(char *str1, t_shell *shell, char *ret)
{
	char tmp[3];
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
		LINE;
		CLEAR_LN;
		print_interp();
		free(ret);
		if (shell->lineinfo->spot_hist < (int)shell->history->size - 1)
		{
			shell->lineinfo->spot_hist++;
			shell->lineinfo->linespot = 0;
			ft_putstr(*(char **)vectspot(shell->lineinfo->spot_hist, shell->history));
			return(ft_strdup(*(char **)vectspot(shell->lineinfo->spot_hist, shell->history)));
		}
		else
		{
			shell->lineinfo->linespot = 0;
			ft_putstr(*(char **)vectspot(shell->lineinfo->spot_hist, shell->history));
			return(ft_strdup(*(char **)vectspot(shell->lineinfo->spot_hist, shell->history)));
		}
	}
	else if (str1[2] == 'B')	//down
	{
		LINE;
		CLEAR_LN;
		print_interp();
		free(ret);
		if (shell->lineinfo->spot_hist > -1)
		{
			shell->lineinfo->spot_hist--;
			if (shell->lineinfo->spot_hist > -1)
			{
				shell->lineinfo->linespot = 0;
				ft_putstr(*(char **)vectspot(shell->lineinfo->spot_hist, shell->history));
				return(ft_strdup(*(char **)vectspot(shell->lineinfo->spot_hist, shell->history)));
			}
			else if (shell->lineinfo->spot_hist == -1)
			{
				shell->lineinfo->linespot = 0;
				ft_putstr("");
				return(ft_strdup(""));
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
			ret = del_fun(ret, shell->lineinfo->linespot);
		}
	}
	else if (str1[2] == '1')
	{
		ft_bzero(tmp, 3);
		read(0, tmp, 3);
		if (tmp[1] == 'D')
			jumpleft(shell, ret);
		if (tmp[1] == 'C')
			jumpright(shell, ret);
		// if (tmp[1] == 'A')
		// 	ft_putstr("SHIFT UP");
		// if (tmp[1] == 'B')
		// 	ft_putstr("SHIFT DOWN");
	}

	return(ft_strjoin(ret, ""));
}

int isjustwhite(char *str)
{
	int i;

	i = 0;
	while(str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	if (str[i])
		return 0;
	return (1);
}

char	*read_tmp(t_shell *shell)
{
	char		*str1;
	char		*ret;
	char		*tmp;
	int i;

	i = 0;
	ret = ft_strnew(0);
	str1 = ft_strnew(BUFF_SIZE);
	termresetline(shell);
	while (1)
	{
		bzero(str1, BUFF_SIZE);
		read(0, str1, BUFF_SIZE);
		if (str1[0] == 13 && !shell->lineinfo->dq)
		{
			free(str1);
			break;
		}
		else if (str1[0] == 13 && shell->lineinfo->dq)
		{
			INSERT_MODE_ON;
			ft_putchar('\n');
			INSERT_MODE_OFF;
			i++;
		}
		if (check_char(str1, shell) || (shell->lineinfo->dq && str1[0] == 13))
		{
			INSERT_MODE_ON;
			ft_putstr(str1);
			INSERT_MODE_OFF;
			if (str1[0] == 13)
				str1[0] = '\n';
			ret = addtobuff(shell, ret, str1);
			shell->lineinfo->size++;
		}
		else
			ret = checkarrowkeys(str1, shell, ret);
	}
	ft_putchar('\n');
	if (ft_strcmp("", ret) && shell->lineinfo->spot_hist == -1 && ft_strcmp(vectspot(0, shell->history), ret) != 0 && !isjustwhite(ret))
	{
		tmp = ft_strdup(ret);
		vect_insert(shell->history, 0, &tmp);
	}
	return (ret);
}
