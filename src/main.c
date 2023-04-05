/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: cschabra <cschabra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/09 14:09:19 by cschabra      #+#    #+#                 */
/*   Updated: 2023/04/05 18:32:55 by cschabra      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int32_t	main(int32_t argc, char **argv, char **envp)
{
	t_file	file;
	t_id	pid;
	t_arg	arg;

	arg = (t_arg){.argc = argc, .argv = argv, .envp = envp};
	ft_inputcheck(argc);
	if (pipe(file.fd1) == -1)
		ft_throwerror("pipe error in main", errno);
	ft_makechildren(&arg, &file, &pid);
	if (close(file.fd1[0]) == -1 || close(file.fd1[1]) == -1)
		ft_throwerror("close error in main", errno);
	pid.pidstat = waitpid(pid.pid, &pid.stat, 0);
	if (WIFEXITED(pid.stat))
	{
		pid.statcode = WEXITSTATUS(pid.stat);
		if (pid.statcode != 0)
			exit(pid.statcode);
	}
	return (0);
}
