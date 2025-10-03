#define _POSIX_C_SOURCE 200809L //signals were complaining 
#include "minishell.h"

static void	handle_sigint(int signum)
{
	g_exit_status = signum;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}


void	signal_setup(void)
{
	struct sigaction	sa;

	ft_memset(&sa, 0, sizeof(sa)); //zero errything
	sa.sa_handler = handle_sigint;
	// sigemptyset(&sa.sa_mask);
	// sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
}

// void	signal_setup(void)
// {
// 	struct sigaction	sa;

// 	ft_memset(&sa, 0, sizeof(sa)); //zero errything
// 	if (isatty(STDIN_FILENO))
// 	{
// 		sa.sa_handler = handle_sigint;
// 		sigaction(SIGINT, &sa, NULL);

// 		sa.sa_handler = SIG_IGN;
// 		sigaction(SIGQUIT, &sa, NULL);
// 	}
// 	else
// 	{
// 		sa.sa_handler = SIG_DFL;
// 		sigaction(SIGINT, &sa, NULL);
// 		sigaction(SIGQUIT, &sa, NULL);
// 	}
// }

void	set_child_signals(void)
{
	struct sigaction	sa;

	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = SIG_DFL;
	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
}

void set_parent_wait_signals(void)
{
	struct sigaction	sa;
	
	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = SIG_IGN;
	sigaction(SIGINT, &sa, NULL);
}