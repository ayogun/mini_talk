/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yogun <yogun@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 00:43:56 by yogun             #+#    #+#             */
/*   Updated: 2022/09/05 00:27:22 by yogun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"
#include <stdio.h>

/*
	Values are initialized
*/
void	var_init(t_message *var)
{
	var->char_value = 0;
	var->bit_pos = 0;
}

/*	
	Sigaction is more ortable. 
	I use struct instead of global variable.
	OR bitwise operator transfer the signal. 
	Char bytes are filled from left to right. T
	his is why we shift the bits to the left.
	So, first I fill the last bit then 7th then 6th and so on.
*/
void	action(int sig, siginfo_t *info, void *context)
{
	static t_message	message;

	(void)context;
	if (message.pid != info->si_pid)
		var_init(&message);
	if (info->si_pid)
		message.pid = info->si_pid;
	(message.char_value) = (message.char_value) | (sig == SIGUSR1);
	if (++(message.bit_pos) == 8)
	{
		if (!(message.char_value))
		{
			kill(message.pid, SIGUSR1);
			return ;
		}
		ft_putchar_fd((message.char_value), 1);
		kill(message.pid, SIGUSR2);
		var_init(&message);
	}
	else
		(message.char_value) = (message.char_value) << 1;
}

/*
	If SA_SIGINFO is set and the signal is caught, 
	the signal-catching function shall be entered as:
	void func(int signo, siginfo_t *info, void *context);
	STDOUT_FILENO	1	 standard output file descriptor 
*/
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
