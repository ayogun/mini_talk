/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yogun <yogun@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 00:43:56 by yogun             #+#    #+#             */
/*   Updated: 2022/09/04 19:54:31 by yogun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"
#include <stdio.h>

void	var_init(t_message *var)
{
	var->char_value = 0;
	var->bit_pos = 0;
}

// Why would I use signal while there is a better version of it which is sigaction YAY.
// Sigaction is more ortable. I use struct instead of global variable.
static void	action(int sig, siginfo_t *info, void *context)
{
	pid_t					pid_client;
	static t_message	message;



	(void)context;
	if (message.pid != info->si_pid)
		var_init(&message);

	message.pid = info->si_pid;
	if (info->si_pid)
		pid_client = info->si_pid;
	(message.char_value) = (message.char_value) | (sig == SIGUSR1);
	if (++(message.bit_pos) == 8)
	{
		if (!(message.char_value))
		{
			kill(pid_client, SIGUSR1);
			return ;
		}
		ft_putchar_fd((message.char_value), 1);
		kill(pid_client, SIGUSR2);
		var_init(&message);
	}
	else
		(message.char_value) = (message.char_value) << 1;
}

// If SA_SIGINFO is set and the signal is caught, the signal-catching function shall be entered as:
// void func(int signo, siginfo_t *info, void *context);
// STDOUT_FILENO	1	/* standard output file descriptor */
int	main(void)
{
	struct sigaction	sa;
	pid_t				pid_server;
	
	pid_server = getpid();
	ft_putstr_fd("Server PID: ", STDOUT_FILENO);
	ft_putnbr_fd(pid_server, STDOUT_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);
	sa.sa_sigaction = action;
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
   ft_putchar_fd('\n', 1);
	while (1)
		pause();
	return (0);
}


