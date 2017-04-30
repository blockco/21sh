#include "../headers/minishell.h"

int countword_dq(char *str, int i, char dqbuff)
{
	int c;

	c = 0;
	while(str[i] && (str[i] != dqbuff))
	{
		i++;
		c++;
	}
	return c;
}

int countword(char *str, int i)
{
	int c;
	int dq;
	char dqbuff;

	c = 0;
	while((str[i] && str[i] > 32) || dq)
	{
		if ((str[i] == '"' || str[i] == 39 || str[i] == 40) && !dq)
		{
			dq = 1;
			dqbuff = str[i];
			i++;
		}
		else if (str[i] == dqbuff && dq)
		{
			dq = 0;
			i++;
		}
		else
		{
			i++;
			c++;
		}
	}
	return c;
}

char **new_parse(char *str)
{
	char **ret;
	char *cur;
	char dqbuff;
	int words;
	int c;
	int b;
	int i;
	int dq;
	int curword;

	dq = 0;
	i = 0;
	curword = 0;
	words = 0;
	ret = malloc(sizeof(char*) * 1);
	while(str[i])
	{
		// ft_putchar(str[i]);
		while (str[i] < 33)
			i++;
		if (str[i] && (str[i] == '"' || str[i] == 39 || str[i] == 40))
		{
			// ft_putendl("here");
			ret = ft_realloc(ret, sizeof(char*) * (words + 2));
			if (str[i] == 40)
				dqbuff = 41;
			else
				dqbuff = str[i];
			i++;
			c = countword_dq(str, i, dqbuff);
			cur = ft_strnew(c);
			b = 0;
			while(c > 0)
			{
				cur[b] = str[i];
				i++;
				b++;
				c--;
			}
			ret[words] = ft_strdup(cur);
			free(cur);
			words++;
			i++;
		}
		else if (str[i])
		{
			ret = ft_realloc(ret, sizeof(char*) * (words + 2));
			c = countword(str, i);
			cur = ft_strnew(c);
			b = 0;
			while(c > 0)
			{
				if ((str[i] == '"' || str[i] == 39 || str[i] == 40) && !dq)
				{
					dq = 1;
					dqbuff = str[i];
					i++;
				}
				else if (str[i] == dqbuff && dq)
				{
					dq = 0;
					i++;
				}
				else
				{
					cur[b] = str[i];
					i++;
					b++;
					c--;
				}
			}
			// ft_putendl("here");
			ret[words] = ft_strdup(cur);
			free(cur);
			words++;
		}
		ret[words] = NULL;
	}
	return ret;
}
