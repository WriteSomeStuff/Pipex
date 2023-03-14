/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: cschabra <cschabra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/09 14:09:19 by cschabra      #+#    #+#                 */
/*   Updated: 2023/03/14 15:08:57 by cschabra      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_leaks(void)
{
	system("leaks -q pipex");
}

// allowed functions: open, close, read, write, malloc, free, perror,
// strerror, access, dup, dup2, execve, exit, fork, pipe, unlink, wait, waitpid
int32_t	main(int32_t argc, char **argv)
{
	atexit(ft_leaks);
	if (argc < 5)
	{
		ft_putendl_fd("try: ./pipex infile_name \"cmd1\" \"cmd2\" outfile_name", \
		STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	else
	{
		filecheck(argc, argv);
	}
	return (0);
}
