/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   filecheck.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: cschabra <cschabra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/09 14:05:55 by cschabra      #+#    #+#                 */
/*   Updated: 2023/03/14 17:39:31 by cschabra      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
	// does infile? permission? If so process command, send to outfile
	// use dup2 to swap fds with stdin/stdout
	// int main (int argc, char *argv[], char *envp[])? 
	// where to get commands from? env?? how to implement? split with : ?
	// getexec function??
	// access function to find if command exists and is executable, else throw error
	// if no found exit with 127?
	// use split to split commands from input?
	// run commands with execve
	// pipex should also handle that you can use both relative and absolute paths, access?
// fd[0] - read
// fd[1] - write
int32_t	filecheck(int32_t argc, char **argv)
{
	int	fd;

	if (open(argv[1], O_RDONLY) == -1)
	{
		ft_printf("no such file or directory: %s\n", argv[1]);
		return (EXIT_FAILURE);
	}
	fd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (fd == -1)
	{
		ft_putendl_fd("open error", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	if (write(fd, "qq", strlen("qq")) == -1) // make it write output not argv[1]
	{
		ft_putendl_fd("write error", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	argc = 0;
	close(fd);
	return (0);
}

// 	int		fd[2];
	// int		id;
	// int		x;
	// int		y;

	// y = 0;
	// argv = 0;
	// argc = 0;
	// if (pipe(fd) == -1)
	// {
	// 	ft_putendl_fd("pipe error", STDERR_FILENO);
	// 	return (1);
	// }
	// id = fork();
	// if (id == -1)
	// {
	// 	ft_putendl_fd("fork error", STDERR_FILENO);
	// 	return (2);
	// }
	// if (id == 0)
	// {
	// 	close(fd[0]);
	// 	printf("input a number: ");
	// 	scanf("%d", &x);
	// 	if (write(fd[1], &x, sizeof(int)) == -1)
	// 	{
	// 		ft_putendl_fd("write error", STDERR_FILENO);
	// 		return (3);
	// 	}
	// 	close(fd[1]);
	// }
	// else
	// {
	// 	close(fd[1]);
	// 	if (read(fd[0], &y, sizeof(int)) == -1)
	// 	{
	// 		ft_putendl_fd("read error", STDERR_FILENO);
	// 		return (4);
	// 	}
	// 	y = y * 2;
	// 	close(fd[0]);
	// 	printf("got from child process: %d\n", y);
	// }
	// return (0);