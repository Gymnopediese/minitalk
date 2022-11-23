/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaud <albaud@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 15:58:13 by albaud            #+#    #+#             */
/*   Updated: 2022/10/28 03:23:13 by albaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

char	*message;

void	send_byte(int pid, char c, int size)
{
	int	i;

	i = -1;
	while (++i < size)
	{
		if (c & 0x01)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		c = c >> 1;
		usleep(100);
	}
}

void	send_string(int pid, char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		send_byte(pid, str[i], 8);
}

void	success(int sig)
{
	(void) sig;
	printf("succeed to send the message\n");
}

void	failed(int sig)
{
	(void) sig;
	printf("failed to send the message\n");
}

int	main(int argc, char **argv)
{
	int					pid;

	if (argc == 3)
	{
		pid = atoi(argv[1]);
		send_byte(pid, (char)strlen(argv[2]), 32);
		send_string(pid, argv[2]);
	}
	return (0);
}
