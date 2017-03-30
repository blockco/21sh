#include "../headers/minishell.h"

int			setup_term(t_shell *shell)
{
	// struct termios	new;
	//
	// if (tcgetattr(0, &shell->old) < 0)
	// 	return (-1);
	// new = shell->old;
	// new.c_lflag &= ~(ECHO | ICANON);
	// // new.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
	//
	// new.c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP
	// | INLCR | IGNCR | ICRNL | IXON);
	// new.c_cflag &= ~(CSIZE | PARENB);
	// new.c_cflag |= CS8;
	// new.c_cc[VMIN] = 1;
	// new.c_cc[VTIME] = 0;
	// if (tcsetattr(0, TCSAFLUSH, &new) < 0)
	// 	return (-1);
	// shell->now = &new;

	struct termios	tattr;
	char *term;

	term = getenv("TERM");

	tgetent(NULL, term);
	tcgetattr(STDIN_FILENO, &shell->old);
	// tcgetattr(STDIN_FILENO, &tattr);
	tattr = shell->old;
	tattr.c_iflag &= ~(BRKINT | ISTRIP
	| INPCK | IXON | ICRNL);
	tattr.c_lflag &= ~(ECHO | ICANON);
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

// int			setup_term(t_shell *shell)
// {
// 		struct termios	tattr;
//
// 		tcgetattr(STDIN_FILENO, &shell->old);
// 		tcgetattr(STDIN_FILENO, &tattr);
// 		tattr.c_iflag &= (BRKINT | ISTRIP
// 		 | ICRNL | IXON);
// 		tattr.c_lflag |= ICANON;
// 		// tattr.c_lflag &= ~(ECHO | ICANON);
// 		// tattr.c_oflag &= (OPOST);
// 		tattr.c_cc[VMIN] = 1;
// 		tattr.c_cc[VTIME] = 0;
// 		tcsetattr(STDIN_FILENO, TCSADRAIN, &tattr);
// 		initshellstruct(shell);
// 		shell->now = &tattr;
// 		return (1);
// }

void termresetline(t_shell *shell)
{
	shell->lineinfo->size = 0;
	shell->lineinfo->linespot = 0;
	shell->lineinfo->spot_hist = -1;
}

void initshellstruct(t_shell *shell)
{
	shell->history = vect_new(32, sizeof(char*));
	shell->sorted_h = vect_new(32, sizeof(char*));
	shell->cmd = malloc(sizeof(t_command));
	shell->lineinfo = malloc(sizeof(t_lineman));
}
