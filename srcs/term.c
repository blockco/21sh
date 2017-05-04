#include "../headers/minishell.h"

int			setup_term(t_shell *shell)
{
	struct termios	tattr;
	char *term;

	term = getenv("TERM");

	tgetent(NULL, term);
	tcgetattr(STDIN_FILENO, &shell->old);
	// tcgetattr(STDIN_FILENO, &tattr);
	tattr = shell->old;
	tattr.c_lflag &= ~(ECHO | ICANON);
	tattr.c_iflag &= ~(BRKINT | ISTRIP
	| INPCK | IXON | ICRNL);
	tattr.c_cflag &= ~(CSIZE | PARENB);
	tattr.c_cflag |= CS8;
	// tattr.c_oflag &= (OPOST);
	tattr.c_cc[VMIN] = 1;
	tattr.c_cc[VTIME] = 0;
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &tattr);
	KEYS_ON;
	initshellstruct(shell);
	return (1);
}

void termresetline(t_shell *shell)
{
	shell->lineinfo->size = 0;
	shell->lineinfo->linespot = 0;
	shell->lineinfo->spot_hist = -1;
	shell->lineinfo->dq = 0;
	shell->endl = 1;
	shell->std_out = dup(1);
	shell->std_in = dup(0);
}

void initshellstruct(t_shell *shell)
{
	shell->history = vect_new(32, sizeof(char*));
	shell->lineinfo = malloc(sizeof(t_lineman));
}

void freeshell(t_shell *shell)
{
	int i;

	i = 0;
	while (i < (int)shell->history->size)
	{
		free(*(char **)vectspot(i, shell->history));
		vect_delete(shell->history,i);
		i++;
	}
	free (shell->history);
	free(shell->lineinfo);
}
