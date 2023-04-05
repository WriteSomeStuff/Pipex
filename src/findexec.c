/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   findexec.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: cschabra <cschabra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/28 17:34:07 by cschabra      #+#    #+#                 */
/*   Updated: 2023/04/05 18:28:14 by cschabra      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	ft_access_and_exec(char	*path, char **cmd, char **envp)
{
	if (access(path, F_OK) == 0)
	{
		if (execve(path, cmd, envp) == -1)
			ft_throwerror("execve error", errno);
	}
}

static void	ft_try_paths(char **path, char **cmd, char **envp)
{
	int32_t	i;
	char	*cmdpath;
	char	*temp;

	i = 0;
	while (path[i])
	{
		temp = ft_strjoin(path[i], "/");
		if (!temp)
			ft_throwerror("strjoin error temp", -1);
		cmdpath = ft_strjoin(temp, cmd[0]);
		if (!cmdpath)
		{
			free(temp);
			ft_throwerror("strjoin error cmdpath", -1);
		}
		free(temp);
		ft_access_and_exec(cmdpath, cmd, envp);
		i++;
	}
}

void	ft_findexec(char *argv, char **envp)
{
	int32_t	i;
	char	**path;
	char	**cmd;

	i = 0;
	ft_cmdcheck(argv);
	cmd = ft_split(argv, ' ');
	if (!cmd)
		ft_throwerror("split error", -1);
	ft_access_and_exec(argv, cmd, envp);
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			path = ft_split(envp[i] + 5, ':');
			if (!path)
				ft_throwerror("split error", -1);
		}
		i++;
	}
	ft_try_paths(path, cmd, envp);
	ft_putstr_fd("pipex: ", STDERR_FILENO);
	ft_putstr_fd(cmd[0], STDERR_FILENO);
	ft_putendl_fd(": command not found", STDERR_FILENO);
	exit(127);
}
