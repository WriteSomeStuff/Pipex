/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: cschabra <cschabra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/09 14:09:19 by cschabra      #+#    #+#                 */
/*   Updated: 2023/03/13 18:05:04 by cschabra      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
// fd[0] - read
// fd[1] - write
int32_t	main(void)
{
	int	fd[2];
	int	id;
	int	x;
	int	y;

	y = 0;
	if (pipe(fd) == -1)
	{
		ft_putendl_fd("pipe error", STDERR_FILENO);
		return (1);
	}
	id = fork();
	if (id == -1)
	{
		ft_putendl_fd("fork error", STDERR_FILENO);
		return (2);
	}
	if (id == 0)
	{
		close(fd[0]);
		printf("input a number: ");
		scanf("%d", &x);
		if (write(fd[1], &x, sizeof(int)) == -1)
		{
			ft_putendl_fd("write error", STDERR_FILENO);
			return (3);
		}
		close(fd[1]);
	}
	else
	{
		close(fd[1]);
		if (read(fd[0], &y, sizeof(int)) == -1)
		{
			ft_putendl_fd("read error", STDERR_FILENO);
			return (4);
		}
		y = y * 2;
		close(fd[0]);
		printf("got from child process: %d\n", y);
	}
	return (0);
}
