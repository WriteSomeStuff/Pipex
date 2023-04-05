/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   errors.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: cschabra <cschabra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/28 17:38:13 by cschabra      #+#    #+#                 */
/*   Updated: 2023/04/05 18:35:38 by cschabra      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_cmdcheck(char *argv)
{
	if (argv[0] == '.')
	{
		ft_putstr_fd("pipex: ", STDERR_FILENO);
		ft_putstr_fd(argv, STDERR_FILENO);
		ft_putendl_fd(": no such file or directory", STDERR_FILENO);
		exit(127);
	}
	else if (argv[0] == ' ')
	{
		ft_putstr_fd("pipex: ", STDERR_FILENO);
		ft_putstr_fd(argv, STDERR_FILENO);
		ft_putendl_fd(": command not found", STDERR_FILENO);
		exit(127);
	}
	else if (!argv[0])
	{
		ft_putstr_fd("pipex: ", STDERR_FILENO);
		ft_putstr_fd(argv, STDERR_FILENO);
		ft_putendl_fd(": permission denied", STDERR_FILENO);
		exit(127);
	}
}

void	ft_inputcheck(int32_t argc)
{
	if (argc != 5)
	{
		ft_putendl_fd("try: ./pipex infile_name \"cmd1\" \"cmd2\" outfile_name", \
		STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
}

void	ft_throwerror(char *message, int32_t ernr)
{
	if (ernr == 127)
		exit(ernr);
	perror(message);
	exit(ernr);
}
