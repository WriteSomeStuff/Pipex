/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: cschabra <cschabra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/09 14:09:19 by cschabra      #+#    #+#                 */
/*   Updated: 2023/03/13 13:57:30 by cschabra      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
// fd[0] - read
// fd[1] - write
int32_t	main(void)
{
	int	fd[2];
	int	id;

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
		//do something
	}
	return (0);
}
