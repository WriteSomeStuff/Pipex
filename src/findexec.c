/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   findexec.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: cschabra <cschabra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/28 17:34:07 by cschabra      #+#    #+#                 */
/*   Updated: 2023/03/28 17:35:21 by cschabra      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_findexec(char *argv, char **envp)
{
	int32_t	i;
	char	**path;
	char	*temp;
	char	*cmdpath;
	char	**cmd;

	i = 0;
	cmd = ft_split(argv, ' ');
	if (!cmd)
		ft_throwerror("split error", EXIT_FAILURE);
	if (access(argv, F_OK) == 0)
	{
		if (execve(argv, cmd, envp) == -1)
			ft_throwerror("execve error", errno);
	}
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			path = ft_split(envp[i] + 5, ':');
		i++;
	}
	i = 0;
	while (path[i])
	{
		temp = ft_strjoin(path[i], "/");
		if (!temp)
			ft_throwerror("strjoin error temp", EXIT_FAILURE);
		cmdpath = ft_strjoin(temp, cmd[0]);
		if (!cmdpath)
		{
			free(temp);
			ft_throwerror("strjoin error cmdpath", EXIT_FAILURE);
		}
		free(temp);
		if (access(cmdpath, F_OK) == 0)
		{
			if (execve(cmdpath, cmd, envp) == -1)
				ft_throwerror("exec error", errno);
		}
		i++;
	}
	ft_putendl_fd("command not found", STDERR_FILENO);
	exit(127);
}
