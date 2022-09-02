/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yogun <yogun@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 00:44:06 by yogun             #+#    #+#             */
/*   Updated: 2022/09/03 00:54:43 by yogun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

// kill() is used to send signal to process
int	main(int argc, char *argv[])
{
   int	pid;

   if (argc != 2)
   {
   	printf("client: invalid arguments\n");
   	exit(EXIT_FAILURE);
   }
   pid = atoi(argv[1]);
   kill(pid, SIGUSR1);
   return (0);
}